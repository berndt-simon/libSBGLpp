#pragma once
#include <GL/glew.h>

#include <vector>
#include <memory>

#include "NoCopy.h"
#include "Shader.h"

using shader_ptr_t = std::unique_ptr<Shader>;

class Program : private NoCopy {
public:
	explicit Program(const std::vector<shader_ptr_t>& shaders);
	virtual ~Program();

	GLuint id() const {
		return _programId;
	}

	GLint attribute_location(const GLchar* attribute_name) const;
	GLint attribute_location_checked(const GLchar* attribute_name) const;

	GLint uniform_location(const GLchar* uniform_name) const;
	GLint uniform_location_checked(const GLchar* uniform_name) const;

	GLuint uniform_blockindex(const GLchar* block_name) const;
	GLuint uniform_blockindex_checked(const GLchar* block_name) const;

	void bind_uniformblock(GLuint block_index, GLuint block_binding) const;
	void bind_uniformblock_by_name(const GLchar* block_name, GLuint block_binding) const;
	 		
	// Uniform Stuff
	void set_uniform_1f(GLint uniform, GLfloat v0) const;
	void set_uniform_2f(GLint uniform, GLfloat v0, GLfloat v1) const;
	void set_uniform_3f(GLint uniform, GLfloat v0, GLfloat v1, GLfloat v2) const;
	void set_uniform_4f(GLint uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void set_uniform_1i(GLint uniform, GLint v0) const;
	void set_uniform_2i(GLint uniform, GLint v0, GLint v1) const;
	void set_uniform_3i(GLint uniform, GLint v0, GLint v1, GLint v2) const;
	void set_uniform_4i(GLint uniform, GLint v0, GLint v1, GLint v2, GLint v3) const;
	void set_uniform_1ui(GLint uniform, GLuint v0) const;
	void set_uniform_2ui(GLint uniform, GLuint v0, GLuint v1) const;
	void set_uniform_3ui(GLint uniform, GLuint v0, GLuint v1, GLuint v2) const;
	void set_uniform_4ui(GLint uniform, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
	void set_uniform_1fv(GLint uniform, GLsizei  count, GLfloat* v) const;
	void set_uniform_2fv(GLint uniform, GLsizei  count, GLfloat* v) const;
	void set_uniform_3fv(GLint uniform, GLsizei  count, GLfloat* v) const;
	void set_uniform_4fv(GLint uniform, GLsizei  count, GLfloat* v) const;
	void set_uniform_1iv(GLint uniform, GLsizei  count, GLint* v) const;
	void set_uniform_2iv(GLint uniform, GLsizei  count, GLint* v) const;
	void set_uniform_3iv(GLint uniform, GLsizei  count, GLint* v) const;
	void set_uniform_4iv(GLint uniform, GLsizei  count, GLint* v) const;
	void set_uniform_1uiv(GLint uniform, GLsizei  count, GLuint* v) const;
	void set_uniform_2uiv(GLint uniform, GLsizei  count, GLuint* v) const;
	void set_uniform_3uiv(GLint uniform, GLsizei  count, GLuint* v) const;
	void set_uniform_4uiv(GLint uniform, GLsizei  count, GLuint* v) const;
	void set_uniform_matrix_2(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_3(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_4(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_2x3(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_3x2(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_2x4(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_4x2(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_3x4(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	void set_uniform_matrix_4x3(GLint uniform, GLsizei  count, GLboolean transpose, GLfloat* m) const;
	
private:
	GLuint _programId;

	static	void show_program_error(GLuint program_id);
};

