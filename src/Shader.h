#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>

#include "NoCopy.h"

class Shader;
using shader_ptr_t = std::unique_ptr<Shader>;

class Shader : private NoCopy {
public:
	static shader_ptr_t from_file(GLenum type, const std::string& filename);
	static shader_ptr_t from_source(GLenum type, const std::string& shader_source);

	Shader(GLenum type, const std::string& source);
	virtual ~Shader();

	GLuint id() const {
		return _shaderId;
	}

private:
	GLuint _shaderId;
	
	static void show_shader_error(GLuint shaderId);
};

