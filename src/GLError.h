#pragma once

#include <GL\glew.h>
#include <string>

namespace GLError {
	
	std::string source_to_string(GLenum source);
	std::string type_to_string(GLenum type);
	std::string severity_to_string(GLenum severity);

	void enable_debug_output();

};

