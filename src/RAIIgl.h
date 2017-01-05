#pragma once

#include <gl\glew.h>
#include <glm\mat4x4.hpp>

namespace glRAII {
	
	struct Use_Program {
		explicit Use_Program(GLuint program_id);
		~Use_Program();
	};

	struct Bind_VAO {
		explicit Bind_VAO(GLuint vao_id);
		~Bind_VAO();	
	};

	class MatrixStack_Block {
	public:
		explicit MatrixStack_Block(glm::mat4& current_mat);
		~MatrixStack_Block();
	private:
		glm::mat4 _backup;
		glm::mat4& _target;
	};

	class Map_BufferObject {
	public:
		Map_BufferObject(GLuint object_id, GLsizeiptr length, GLintptr offset = 0, GLbitfield access = (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));
		~Map_BufferObject();

	private:
		GLuint _object_id;
	};

}