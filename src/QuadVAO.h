#pragma once

#include <memory>

#include "VAO.h"
#include "DrawCall.h"
#include "BufferObject.h"

class QuadVAO : public VAO {
public:
	QuadVAO();
	virtual ~QuadVAO() = default;

	static const DrawArraysConfig DRAW_CALL;

private:
	enum BindIdx : GLuint {
		general
	};

	std::unique_ptr<BufferObject> _vertex_data;
};