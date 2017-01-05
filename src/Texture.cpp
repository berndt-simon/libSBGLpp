#include "Texture.h"

#include <array>
#include <vector>

const GLenum Texture2D::TARGET = GL_TEXTURE_2D;
const GLenum Texture2DMultisample::TARGET = GL_TEXTURE_2D_MULTISAMPLE;

Texture::Texture(GLenum target, GLsizei width, GLsizei height)
	: _texture_id(0) 
	, _width(width)
	, _height(height) {
	glCreateTextures(target, 1, &_texture_id);
}

Texture::~Texture() {
	if (glIsTexture(_texture_id)) {
		glDeleteTextures(1, &_texture_id);
	}
}

void Texture::set_wrap_s(GLint wrapMode) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_WRAP_S, wrapMode);
}

void Texture::set_wrap_t(GLint wrapMode) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::set_swizzle_r(GLint swizzle) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_SWIZZLE_R, swizzle);
}

void Texture::set_swizzle_g(GLint swizzle) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_SWIZZLE_G, swizzle);
}

void Texture::set_swizzle_b(GLint swizzle) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_SWIZZLE_B, swizzle);
}

void Texture::set_swizzle_a(GLint swizzle) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_SWIZZLE_A, swizzle);
}

void Texture::set_min_filter(GLint filter) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::set_mag_filter(GLint filter) const {
	glTextureParameteri(_texture_id, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::bind(GLuint textureUnit) const {
	glBindTextureUnit(textureUnit, _texture_id);
}

void Texture::unbind(GLuint textureUnit) {
	glBindTextureUnit(textureUnit, 0);
}

bool Texture::matches(GLsizei width, GLsizei height) const {
	return _width == width && _height == height;
}

Texture2D::Texture2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	: Texture(TARGET, width, height) {
	glTextureStorage2D(_texture_id, levels, internalformat, width, height);
}

void Texture2D::context_bind() const {
	glBindTexture(TARGET, _texture_id);
}

void Texture2D::context_unbind() {
	glBindTexture(TARGET, 0);
}

void Texture2D::upload_data(GLenum format, GLenum type, const GLvoid* pixels) const {
	glTextureSubImage2D(_texture_id, 0, 0, 0, _width, _height, format, type, pixels);
}

void Texture2D::upload_data(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) const {
	glTextureSubImage2D(_texture_id, level, xoffset, yoffset, width, height, format, type, pixels);
}

void Texture2D::upload_compressed_data(GLenum format, GLsizei image_size, const GLvoid* pixels) const {
	glCompressedTextureSubImage2D(_texture_id, 0, 0, 0, _width, _height, format, image_size, pixels);
}

void Texture2D::upload_compressed_data(GLint level, GLint x_offset, GLint y_offset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid* pixels) const {
	glCompressedTextureSubImage2D(_texture_id, level, x_offset, y_offset, width, height, format, image_size, pixels);
}

Texture2DMultisample::Texture2DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	: Texture(TARGET, width, height) {
	glTextureStorage2DMultisample(_texture_id, samples, internalformat, width, height, fixedsamplelocations);
}

void Texture2DMultisample::context_bind() const {
	glBindTexture(TARGET, _texture_id);
}

void Texture2DMultisample::context_unbind() {
	glBindTexture(TARGET, 0);
}

#pragma region dds_stuff

static const uint32_t DDS_MAGIC_NUMBER(0x20534444);		// Equivalent to "DDS " in ASCII
static const uint32_t FOURCC_DXT1(0x31545844);			// Equivalent to "DXT1" in ASCII
static const uint32_t FOURCC_DXT3(0x33545844);			// Equivalent to "DXT3" in ASCII
static const uint32_t FOURCC_DXT5(0x35545844);			// Equivalent to "DXT5" in ASCII

														// Read any Type from a iStream into a corresponding Pointer-Target
template<typename T>
static inline void read(std::istream& file, T* dst) {
	file.read(reinterpret_cast<char*>(dst), sizeof(T));
}

// Read any Type from a iStream and return the Value by Copy
template<typename T>
static inline T read(std::istream& file) {
	union {
		T buffer;
		char as_chars[sizeof(T)];
	};
	file.read(as_chars, sizeof(T));
	return buffer;
}

std::unique_ptr<Texture2D> Texture2D::load_dds(std::istream& in) {

	/* verify the type of file */
	if (read<uint32_t>(in) != DDS_MAGIC_NUMBER) {
		return std::unique_ptr<Texture2D>(nullptr);
	}

	struct dds_pixelformat_t {
		uint32_t size;
		uint32_t flags;
		uint32_t four_cc;
		uint32_t rgb_bitcount;
		uint32_t r_bitmask;
		uint32_t g_bitmask;
		uint32_t b_bitmask;
		uint32_t a_bitmask;
	};

	static_assert(sizeof(dds_pixelformat_t) == 32, "Sizeof Mismatch");
	static_assert(alignof(dds_pixelformat_t) == alignof(uint32_t), "Sizeof Mismatch");

	struct dds_header_t {
		uint32_t size;
		uint32_t flags;
		uint32_t height;
		uint32_t width;
		uint32_t pitch_or_linear_size;
		uint32_t depth;
		uint32_t mipmap_count;
		std::array<uint32_t, 11> reserved1;
		dds_pixelformat_t pixelformat;
		uint32_t caps;
		uint32_t caps2;
		uint32_t caps3;
		uint32_t caps4;
		uint32_t reserved2;
	} header{};

	static_assert(sizeof(dds_header_t) == 124, "Sizeof Mismatch");

	/* get the surface desc */
	read(in, &header);

	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = header.mipmap_count > 1 ? header.pitch_or_linear_size * 2 : header.pitch_or_linear_size;
	std::vector<unsigned char> buffer(bufsize);
	in.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

	unsigned int components = (header.pixelformat.four_cc == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (header.pixelformat.four_cc) {
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			return std::unique_ptr<Texture2D>(nullptr);
	}

	auto tex = std::make_unique<Texture2D>(header.mipmap_count + 1, format, header.width, header.height);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	
	{
		tex->context_bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize((format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16);
		unsigned int offset(0);

		/* load the mipmaps */
		for (auto mipmap_level(0U); mipmap_level < (header.mipmap_count + 1) && (header.width || header.height); ++mipmap_level) {
			unsigned int size = ((header.width + 3) / 4) * ((header.height + 3) / 4) * blockSize;
			tex->upload_compressed_data(mipmap_level, 0, 0, header.width, header.height, format, size, buffer.data() + offset);

			offset += size;
			header.width /= 2;
			header.height /= 2;

			if (header.width < 1) {
				header.width = 1;
			}
			if (header.height < 1) {
				header.height = 1;
			}
		}
		tex->context_unbind();
	}
	return tex;
}

#pragma endregion


