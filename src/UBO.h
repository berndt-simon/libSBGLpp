#pragma once
 
#include "BufferObject.h"

template<typename T>
class UBO : protected BufferObject {
public:
	explicit UBO(GLenum usage = GL_DYNAMIC_DRAW) 
		: BufferObject(GL_UNIFORM_BUFFER) {
		init(usage);
	}
	~UBO() = default;

	T& data() {
		return _data;
	};

	const T& data() const {
		return _data;
	};

	void buffer() const {
		BufferObject::buffer_sub(&_data, sizeof(_data));
	};

	void bind(GLuint blockBinding) const {
		glBindBufferBase(_target, blockBinding, _objectId);
	};

protected:
	void init(GLenum usage = GL_DYNAMIC_DRAW) const {
		BufferObject::buffer(&_data, sizeof(_data), usage);
	};

private:
	T _data;

};