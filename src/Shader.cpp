#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


Shader::Shader(GLenum type, const std::string& source) : _shaderId(0) {
	_shaderId = glCreateShader(type);

	const GLchar* code = static_cast<const GLchar*>(source.c_str());
	glShaderSource(_shaderId, 1, &code, nullptr);
	glCompileShader(_shaderId);

	GLint status;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		show_shader_error(_shaderId);

		glDeleteShader(_shaderId);
		_shaderId = 0;

		throw;
	}
}


Shader::~Shader() {
	if (glIsShader(_shaderId)) {
		glDeleteShader(_shaderId);
	}
}

std::unique_ptr<Shader> Shader::from_file(GLenum type, const std::string& filePath) {
	std::ifstream file;
	file.open(filePath, std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error("Can't open Shader-File");
	}

	std::stringstream init;
	init << file.rdbuf();

	return std::make_unique<Shader>(type, init.str());
}

std::unique_ptr<Shader> Shader::from_source(GLenum type, const std::string& sourceCode) {
	return std::make_unique<Shader>(type, sourceCode);
}

void Shader::show_shader_error(GLuint shaderId) {
	std::cerr << "Compile Failure in Shader:" << std::endl;
	GLint infoLogLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::unique_ptr<GLchar[]> strInfoLog = std::make_unique<GLchar[]>(infoLogLength + 1);
	glGetShaderInfoLog(shaderId, infoLogLength, nullptr, strInfoLog.get());
	std::cerr << strInfoLog.get() << std::endl;
}
