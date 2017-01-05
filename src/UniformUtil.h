#pragma once
#include <GL/glew.h>

namespace Uniform {

	template<typename... T>
	void set_uniform(GLint location, T... t);
	
	template<typename... T>
	void set_program_uniform(GLuint program, GLint location, T... t);

	template<GLsizei N, typename... T>
	void set_uniform_vector(GLint location, T... t);

}