#pragma once

#include <GL/glew.h>
#include "NoCopy.h"

class VAO : private NoCopy {
public:
	VAO();
	virtual ~VAO();

	GLuint id() const {
		return _vaoId;
	}

private:
	void bind() const;
	static void unbind();

	GLuint _vaoId;
};

