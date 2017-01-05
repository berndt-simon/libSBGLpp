#include "Bitmap.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unique_ptr<Bitmap> Bitmap::from_file(const std::string& filename, int reqComponents) {
	int width(0);
	int height(0);
	int components(0);
	unsigned char* data(stbi_load(filename.c_str(), &width, &height, &components, reqComponents));
	if (data == nullptr) {
		throw 0;
	}
	GLenum format;
	if (reqComponents != 0) {
		components = reqComponents;
	}
	switch (components) {
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			throw 0;
	}
	std::unique_ptr<Bitmap> bitmap = std::make_unique<Bitmap>(width, height, format, GL_BYTE, data);
	stbi_image_free(data);
	return bitmap;
}

Bitmap::Bitmap(GLuint width, GLuint height, GLenum format, GLenum type, byte_t* data) 
	: _width(width)
	, _height(height)
	, _format(format)
	, _type(type)
	, _data(nullptr) {
	if (data != nullptr) {
		const size_t byteCnt(sizeof_pixel() * _width * _height);
		_data = static_cast<byte_t*>(malloc(byteCnt));
		memcpy(_data, data, byteCnt);
	}	
}

Bitmap::~Bitmap() {
	if(_data != nullptr) {
		free(_data);
		_data = nullptr;
	}
}

const GLvoid* Bitmap::data() const {
	return _data;
}

const void* Bitmap::pixel(unsigned int column, unsigned int row) const {
	const unsigned int idx((row * _width) + column);
	const size_t offset(sizeof_pixel() * idx);
	return &(_data[0]) + offset;
}

void Bitmap::set_pixel(unsigned int column, unsigned int row, const void* pixelData) {
	const unsigned int idx((row * _width) + column);
	const size_t offset(sizeof_pixel() * idx);
	memcpy(&(_data[0]) + offset, pixelData, sizeof_pixel());
}

size_t Bitmap::sizeof_pixel() const {
	switch (_type) {
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char) * channel_count();
		case GL_BYTE:
			return sizeof(char) * channel_count();
		case GL_UNSIGNED_SHORT:
			return sizeof(unsigned short) * channel_count();
		case GL_SHORT:
			return sizeof(short) * channel_count();
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int) * channel_count();
		case GL_INT:
			return sizeof(int) * channel_count();
		case GL_FLOAT:
			return sizeof(float) * channel_count();
		case GL_UNSIGNED_BYTE_3_3_2:
		case GL_UNSIGNED_BYTE_2_3_3_REV:
			return sizeof(unsigned char);
		case GL_UNSIGNED_SHORT_5_6_5:
		case GL_UNSIGNED_SHORT_5_6_5_REV:
		case GL_UNSIGNED_SHORT_4_4_4_4:
		case GL_UNSIGNED_SHORT_4_4_4_4_REV:
		case GL_UNSIGNED_SHORT_5_5_5_1:
		case GL_UNSIGNED_SHORT_1_5_5_5_REV:
			return sizeof(unsigned short);
		case GL_UNSIGNED_INT_8_8_8_8:
		case GL_UNSIGNED_INT_8_8_8_8_REV:
		case GL_UNSIGNED_INT_10_10_10_2:
		case GL_UNSIGNED_INT_2_10_10_10_REV:
			return sizeof(unsigned int);
		default:
			throw 0;
	}
}

unsigned int Bitmap::channel_count() const {
	switch (_format) {
		case GL_RED:
			return 1;
		case GL_RG:
			return 2;
		case GL_RGB:
			return 3;
		case GL_BGR:
			return 3;
		case GL_RGBA:
			return 4;
		case GL_BGRA:
			return 4;
		case GL_RED_INTEGER:
			return 1;
		case GL_RG_INTEGER:
			return 2;
		case GL_RGB_INTEGER:
			return 3;
		case GL_BGR_INTEGER:
			return 3;
		case GL_RGBA_INTEGER:
			return 4;
		case GL_BGRA_INTEGER:
			return 4;
		case GL_STENCIL_INDEX:
			return 1;
		case GL_DEPTH_COMPONENT:
			return 1;
		case GL_DEPTH_STENCIL:
			return 2;
		default:
			throw 0;
	}
}
