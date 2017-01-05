#pragma once

#include <GL/glew.h>

#include "NoCopy.h"
#include "RAIIgl.h"

class BufferObject : private NoCopy {	
public:
	explicit BufferObject(GLenum target = GL_ARRAY_BUFFER);
	virtual ~BufferObject();

	GLuint id() const {
		return _objectId;
	}

	GLenum target() const {
		return _target;
	}

	void buffer(const GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) const;
	void buffer_sub(const GLvoid* data, GLsizeiptr size, GLintptr offset = 0) const;
	
protected:
	GLenum _target;
	GLuint _objectId;
};