#include "VAO.h"
#include <iostream>

VAO::VAO() : _vaoId(0) {
	glCreateVertexArrays(1, &_vaoId);
}

VAO::~VAO() {
	if (glIsVertexArray(_vaoId)) {
		glDeleteVertexArrays(1, &_vaoId);
	}
}

void VAO::bind() const {
	glBindVertexArray(_vaoId);
}

void VAO::unbind() {
	glBindVertexArray(0);
}
