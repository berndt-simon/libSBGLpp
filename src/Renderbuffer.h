#pragma once
#include "NoCopy.h"

#include <GL/glew.h>

class Renderbuffer : private NoCopy {
public:
	Renderbuffer(GLenum internalformat, GLsizei width, GLsizei height);
	Renderbuffer(GLenum internalformat, GLsizei width, GLsizei height, GLsizei samples);
	virtual ~Renderbuffer();


	GLuint id() const {
		return _buffer_id;
	}

	GLsizei width() const {
		return _width;
	}

	GLsizei height() const {
		return _height;
	}

	bool matches(GLsizei width, GLsizei height) const;

private:
	Renderbuffer(GLsizei width, GLsizei height);

	GLuint _buffer_id;
	const GLsizei _width;
	const GLsizei _height;
};