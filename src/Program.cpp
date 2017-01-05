#include "Program.h"
#include <iostream>
#include "UniformUtil.h"

Program::Program(const std::vector<std::unique_ptr<Shader>>& shaders) : _programId(0) {
	_programId = glCreateProgram();

	for (auto sItter(shaders.begin()); sItter != shaders.end(); ++sItter) {
		glAttachShader(_programId, (*sItter)->id());
	}

	glLinkProgram(_programId);

	for (auto sItter(shaders.begin()); sItter != shaders.end(); ++sItter) {
		glDetachShader(_programId, (*sItter)->id());
	}

	GLint status;
	glGetProgramiv(_programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		show_program_error(_programId);

		glDeleteProgram(_programId);
		_programId = 0;

		throw;
	}
}

Program::~Program() {
	if (glIsProgram(_programId)) {
		glDeleteProgram(_programId);
	}
}

GLint Program::attribute_location(const GLchar* attributeName) const {
	return glGetAttribLocation(_programId, attributeName);
}

GLint Program::attribute_location_checked(const GLchar* attributeName) const {
	GLint attributeLocation(glGetAttribLocation(_programId, attributeName));
	if (attributeLocation == -1) {
		throw std::runtime_error("Invalid Attribute-Location");
	}
	return attributeLocation;
}

GLint Program::uniform_location(const GLchar* uniformName) const {
	return glGetUniformLocation(_programId, uniformName);
}

GLint Program::uniform_location_checked(const GLchar* uniformName) const {
	GLint uniformLocation(glGetUniformLocation(_programId, uniformName));
	if (uniformLocation == -1) {
		throw std::runtime_error("Invalid Uniform-Location");
	}
	return uniformLocation;
}

GLuint Program::uniform_blockindex(const GLchar* blockName) const {
	return glGetUniformBlockIndex(_programId, blockName);
}

GLuint Program::uniform_blockindex_checked(const GLchar* blockName) const {
	GLuint blockIndex(glGetUniformBlockIndex(_programId, blockName));
	if (blockIndex == GL_INVALID_INDEX) {
		throw std::runtime_error("Invalid Block-Index");
	}
	return blockIndex;
}

void Program::bind_uniformblock(GLuint uniformBlockIndex, GLuint uniformBlockBinding) const {
	glUniformBlockBinding(_programId, uniformBlockIndex, uniformBlockBinding);
}

void Program::bind_uniformblock_by_name(const GLchar* block_name, GLuint block_binding) const {
	bind_uniformblock(uniform_blockindex(block_name), block_binding);
}

void Program::show_program_error(GLuint programId) {
	std::cerr << "Program linking failure:" << std::endl;
	GLint infoLogLength;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::unique_ptr<GLchar[]> strInfoLog = std::make_unique<GLchar[]>(infoLogLength + 1);
	glGetProgramInfoLog(programId, infoLogLength, nullptr, strInfoLog.get());
	std::cerr << strInfoLog.get() << std::endl;
}

void Program::set_uniform_1f(GLint uniform, GLfloat v0) const {
	glProgramUniform1f(_programId, uniform, v0);
}
void Program::set_uniform_2f(GLint uniform, GLfloat v0, GLfloat v1) const {
	glProgramUniform2f(_programId, uniform, v0, v1);
}
void Program::set_uniform_3f(GLint uniform, GLfloat v0, GLfloat v1, GLfloat v2) const {
	glProgramUniform3f(_programId, uniform, v0, v1, v2);
}
void Program::set_uniform_4f(GLint uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
	glProgramUniform4f(_programId, uniform, v0, v1, v2, v3);
}
void Program::set_uniform_1i(GLint uniform, GLint v0) const {
	glProgramUniform1i(_programId, uniform, v0);
}
void Program::set_uniform_2i(GLint uniform, GLint v0, GLint v1) const {
	glProgramUniform2i(_programId, uniform, v0, v1);
}
void Program::set_uniform_3i(GLint uniform, GLint v0, GLint v1, GLint v2) const {
	glProgramUniform3i(_programId, uniform, v0, v1, v2);
}
void Program::set_uniform_4i(GLint uniform, GLint v0, GLint v1, GLint v2, GLint v3) const {
	glProgramUniform4i(_programId, uniform, v0, v1, v2, v3);
}
void Program::set_uniform_1ui(GLint uniform, GLuint v0) const {
	glProgramUniform1ui(_programId, uniform, v0);
}
void Program::set_uniform_2ui(GLint uniform, GLuint v0, GLuint v1) const {
	glProgramUniform2ui(_programId, uniform, v0, v1);
}
void Program::set_uniform_3ui(GLint uniform, GLuint v0, GLuint v1, GLuint v2) const {
	glProgramUniform3ui(_programId, uniform, v0, v1, v2);
}
void Program::set_uniform_4ui(GLint uniform, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
	glProgramUniform4ui(_programId, uniform, v0, v1, v2, v3);
}
void Program::set_uniform_1fv(GLint uniform, GLsizei count, GLfloat* v) const {
	glProgramUniform1fv(_programId, uniform, count, v);
}
void Program::set_uniform_2fv(GLint uniform, GLsizei count, GLfloat* v) const {
	glProgramUniform2fv(_programId, uniform, count, v);
}
void Program::set_uniform_3fv(GLint uniform, GLsizei count, GLfloat* v) const {
	glProgramUniform3fv(_programId, uniform, count, v);
}
void Program::set_uniform_4fv(GLint uniform, GLsizei count, GLfloat* v) const {
	glProgramUniform4fv(_programId, uniform, count, v);
}
void Program::set_uniform_1iv(GLint uniform, GLsizei count, GLint* v) const {
	glProgramUniform1iv(_programId, uniform, count, v);
}
void Program::set_uniform_2iv(GLint uniform, GLsizei count, GLint* v) const {
	glProgramUniform2iv(_programId, uniform, count, v);
}
void Program::set_uniform_3iv(GLint uniform, GLsizei count, GLint* v) const {
	glProgramUniform3iv(_programId, uniform, count, v);
}
void Program::set_uniform_4iv(GLint uniform, GLsizei count, GLint* v) const {
	glProgramUniform4iv(_programId, uniform, count, v);
}
void Program::set_uniform_1uiv(GLint uniform, GLsizei count, GLuint* v) const {
	glProgramUniform1uiv(_programId, uniform, count, v);
}
void Program::set_uniform_2uiv(GLint uniform, GLsizei count, GLuint* v) const {
	glProgramUniform2uiv(_programId, uniform, count, v);
}
void Program::set_uniform_3uiv(GLint uniform, GLsizei count, GLuint* v) const {
	glProgramUniform3uiv(_programId, uniform, count, v);
}
void Program::set_uniform_4uiv(GLint uniform, GLsizei count, GLuint* v) const {
	glProgramUniform4uiv(_programId, uniform, count, v);
}
void Program::set_uniform_matrix_2(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix2fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_3(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix3fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_4(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix4fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_2x3(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix2x3fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_3x2(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix3x2fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_2x4(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix2x4fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_4x2(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix4x2fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_3x4(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix3x4fv(_programId, uniform, count, transpose, m);
}
void Program::set_uniform_matrix_4x3(GLint uniform, GLsizei count, GLboolean transpose, GLfloat* m) const {
	glProgramUniformMatrix4x3fv(_programId, uniform, count, transpose, m);
}