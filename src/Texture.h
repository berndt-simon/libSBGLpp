#pragma once

#include "NoCopy.h"
#include "Bitmap.h"

#include <GL/glew.h>

class Texture : private NoCopy {
public:
	Texture(GLenum target, GLsizei width, GLsizei height);
	virtual ~Texture();

	void set_wrap_s(GLint wrap_mode) const;
	void set_wrap_t(GLint wrap_mode) const;

	void set_swizzle_r(GLint swizzle) const;
	void set_swizzle_g(GLint swizzle) const;
	void set_swizzle_b(GLint swizzle) const;
	void set_swizzle_a(GLint swizzle) const;

	void set_min_filter(GLint filter) const;
	void set_mag_filter(GLint filter) const;

	void bind(GLuint texture_unit) const;
	static void unbind(GLuint texture_unit);

	GLuint id() const {
		return _texture_id;
	}

	GLsizei width() const {
		return _width;
	}

	GLsizei height() const {
		return _height;
	}

	bool matches(GLsizei width, GLsizei height) const;

protected:
	GLuint _texture_id;
	GLsizei _width;
	GLsizei _height;
};


class Texture2D : public Texture {
public:
	Texture2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	virtual ~Texture2D() = default;


	void upload_data(GLenum format, GLenum type, const GLvoid* pixels) const;
	void upload_data(GLint level, GLint x_offset, GLint y_offset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) const;


	void upload_compressed_data(GLenum format, GLsizei image_size, const GLvoid* pixels) const;
	void upload_compressed_data(GLint level, GLint x_offset, GLint y_offset, GLsizei width, GLsizei height, GLenum format, GLsizei image_size, const GLvoid* pixels) const;


	static std::unique_ptr<Texture2D> load_dds(std::istream& in);

private:
	void context_bind() const;
	static void context_unbind();

	static const GLenum TARGET;
};

class Texture2DMultisample : public Texture {
public:
	Texture2DMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	virtual ~Texture2DMultisample() = default;

private:
	void context_bind() const;
	static void context_unbind();

	static const GLenum TARGET;
};
