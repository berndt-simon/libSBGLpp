#include "BufferObject.h"

BufferObject::BufferObject(GLenum target)	
	:_target(target)
	, _objectId(0) {
	glCreateBuffers(1, &_objectId);
}

BufferObject::~BufferObject() {
	if (glIsBuffer(_objectId)) {
		glDeleteBuffers(1, &_objectId);
	}
}

void BufferObject::buffer(const GLvoid* data, GLsizeiptr size, GLenum usage) const {
	glNamedBufferData(_objectId, size, data, usage);
}

void BufferObject::buffer_sub(const GLvoid* data, GLsizeiptr size, GLintptr offset) const {
	glNamedBufferSubData(_objectId, offset, size, data);
}

