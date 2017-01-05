#pragma once
#include "NoCopy.h"
#include <GL/glew.h>

#include <string>
#include <memory>

using byte_t = unsigned char;

class Bitmap : private NoCopy {
public:

	static std::unique_ptr<Bitmap> from_file(const std::string& filename, int reqComponents = 0);

	Bitmap::Bitmap(GLuint width, GLuint height, GLenum format, GLenum type, byte_t* data = nullptr);
	virtual ~Bitmap();

	GLuint width() const {
		return _width;
	}

	GLuint height() const {
		return _height;
	}

	GLenum format() const {
		return _format;
	}

	GLenum type() const {
		return _type;
	}

	const GLvoid* data() const;

	const void* pixel(unsigned int column, unsigned int row) const;
	void set_pixel(unsigned int  column, unsigned int  row, const void* pixelData);

	size_t sizeof_pixel() const;

protected:
	unsigned int channel_count() const;

private:
	GLenum _format;
	GLenum _type;

	GLuint _width;
	GLuint _height;

	byte_t* _data;
};