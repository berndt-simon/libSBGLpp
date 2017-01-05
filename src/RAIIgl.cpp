#include "RAIIgl.h"

namespace glRAII {

	Use_Program::Use_Program(GLuint program_id) {
		glUseProgram(program_id);
	}

	Use_Program::~Use_Program() {
		glUseProgram(0);
	}

	Bind_VAO::Bind_VAO(GLuint vao_id) {
		glBindVertexArray(vao_id);
	}

	Bind_VAO::~Bind_VAO() {
		glBindVertexArray(0);
	}

	MatrixStack_Block::MatrixStack_Block(glm::mat4& current)
		: _target(current)
		, _backup(current) {		
	}

	MatrixStack_Block::~MatrixStack_Block() {
		_target = _backup;
	}

	Map_BufferObject::Map_BufferObject(GLuint object_id, GLsizeiptr length, GLintptr offset, GLbitfield access)
		: _object_id(object_id) {
		glMapNamedBufferRange(_object_id, offset, length, access);
	}

	Map_BufferObject::~Map_BufferObject() {
		glUnmapNamedBuffer(_object_id);
	}

}

