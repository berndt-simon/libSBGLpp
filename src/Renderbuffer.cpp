#include "Renderbuffer.h"

Renderbuffer::Renderbuffer(GLenum internalformat, GLsizei width, GLsizei height) 
	: Renderbuffer(width, height) {
	glNamedRenderbufferStorage(_buffer_id, internalformat, width, height);
}

Renderbuffer::Renderbuffer(GLenum internalformat, GLsizei width, GLsizei height, GLsizei samples) 
	: Renderbuffer(width, height) {
	glNamedRenderbufferStorageMultisample(_buffer_id, samples, internalformat, width, height);
}

Renderbuffer::~Renderbuffer() {
	if (glIsRenderbuffer(_buffer_id)) {
		glDeleteRenderbuffers(1, &_buffer_id);
	}
}

bool Renderbuffer::matches(GLsizei width, GLsizei height) const {
	return _width == width && _height == height;
}

Renderbuffer::Renderbuffer(GLsizei width, GLsizei height)
	: _buffer_id(0)
	, _width(width)
	, _height(height) {
	glCreateRenderbuffers(1, &_buffer_id);
}
