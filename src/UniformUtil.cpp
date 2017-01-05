#include "UniformUtil.h"

namespace Uniform {

	// 1f
	template<>
	void set_uniform<GLfloat>(GLint location, GLfloat v0) {
		glUniform1f(location, v0);
	}

	template<>
	void set_program_uniform<GLfloat>(GLuint program, GLint location, GLfloat v0) {
		glProgramUniform1f(program, location, v0);
	}

	// 2f
	template<>
	void set_uniform<GLfloat, GLfloat>(GLint location, GLfloat v0, GLfloat v1) {
		glUniform2f(location, v0, v1);
	}

	template<>
	void set_program_uniform<GLfloat>(GLuint program, GLint location, GLfloat v0, GLfloat v1) {
		glProgramUniform2f(program, location, v0, v1);
	}

	template<>
	void set_uniform<GLfloat, GLfloat, GLfloat>(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
		glUniform3f(location, v0, v1, v2);
	}

	template<>
	void set_uniform<GLfloat, GLfloat, GLfloat, GLfloat>(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
		glUniform4f(location, v0, v1, v2, v3);
	}

	template<>
	void set_uniform<GLint>(GLint location, GLint v0) {
		glUniform1i(location, v0);
	}

	template<>
	void set_uniform<GLint, GLint>(GLint location, GLint v0, GLint v1) {
		glUniform2i(location, v0, v1);
	}

	template<>
	void set_uniform<GLint, GLint, GLint>(GLint location, GLint v0, GLint v1, GLint v2) {
		glUniform3i(location, v0, v1, v2);
	}

	template<>
	void set_uniform<GLint, GLint, GLint, GLint>(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
		glUniform4i(location, v0, v1, v2, v3);
	}

	template<>
	void set_uniform<GLuint>(GLint location, GLuint v0) {
		glUniform1ui(location, v0);
	}

	template<>
	void set_uniform<GLuint, GLuint>(GLint location, GLuint v0, GLuint v1) {
		glUniform2ui(location, v0, v1);
	}

	template<>
	void set_uniform<GLuint, GLuint, GLuint>(GLint location, GLuint v0, GLuint v1, GLuint v2) {
		glUniform3ui(location, v0, v1, v2);
	}

	template<>
	void set_uniform<GLuint, GLuint, GLuint, GLuint>(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
		glUniform4ui(location, v0, v1, v2, v3);
	}

	template<>
	void set_uniform_vector<1, const  GLfloat*>(GLint location, const GLfloat* v) {
		glUniform1fv(location, 1, v);
	}

	template<>
	void set_uniform_vector<2, const GLfloat*>(GLint location, const GLfloat* v) {
		glUniform2fv(location, 2, v);
	}

	template<>
	void set_uniform_vector<3, const GLfloat*>(GLint location, const GLfloat* v) {
		glUniform3fv(location, 3, v);
	}

	template<>
	void set_uniform_vector<4, const GLfloat*>(GLint location, const GLfloat* v) {
		glUniform4fv(location, 4, v);
	}

	template<>
	void set_uniform_vector<1, const GLint*>(GLint location, const GLint* v) {
		glUniform1iv(location, 1, v);
	}

	template<>
	void set_uniform_vector<2, const GLint*>(GLint location, const GLint* v) {
		glUniform2iv(location, 2, v);
	}

	template<>
	void set_uniform_vector<3, const GLint*>(GLint location, const GLint* v) {
		glUniform3iv(location, 3, v);
	}

	template<>
	void set_uniform_vector<4, const GLint*>(GLint location, const GLint* v) {
		glUniform4iv(location, 4, v);
	}

	template<>
	void set_uniform_vector<1, const GLuint*>(GLint location, const GLuint* v) {
		glUniform1uiv(location, 1, v);
	}

	template<>
	void set_uniform_vector<2, const GLuint*>(GLint location, const GLuint* v) {
		glUniform2uiv(location, 2, v);
	}

	template<>
	void set_uniform_vector<3, const GLuint*>(GLint location, const GLuint* v) {
		glUniform3uiv(location, 3, v);
	}

	template<>
	void set_uniform_vector<4, const GLuint*>(GLint location, const GLuint* v) {
		glUniform4uiv(location, 4, v);
	}


	/*
	void glUniform1fv(GLint location,
	GLsizei count,
	const GLfloat *value);

	void glUniform2fv(GLint location,
	GLsizei count,
	const GLfloat *value);

	void glUniform3fv(GLint location,
	GLsizei count,
	const GLfloat *value);

	void glUniform4fv(GLint location,
	GLsizei count,
	const GLfloat *value);

	void glUniform1iv(GLint location,
	GLsizei count,
	const GLint *value);

	void glUniform2iv(GLint location,
	GLsizei count,
	const GLint *value);

	void glUniform3iv(GLint location,
	GLsizei count,
	const GLint *value);

	void glUniform4iv(GLint location,
	GLsizei count,
	const GLint *value);

	void glUniform1uiv(GLint location,
	GLsizei count,
	const GLuint *value);

	void glUniform2uiv(GLint location,
	GLsizei count,
	const GLuint *value);

	void glUniform3uiv(GLint location,
	GLsizei count,
	const GLuint *value);

	void glUniform4uiv(GLint location,
	GLsizei count,
	const GLuint *value);
	*/
}
