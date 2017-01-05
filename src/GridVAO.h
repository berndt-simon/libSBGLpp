#pragma once

#include <memory>

#include "VAO.h"
#include "DrawCall.h"
#include "BufferObject.h"

class GridVAO : public VAO {
public:
	GridVAO(unsigned divisions_u = 0, unsigned divisions_v = 0, float dimension_u = 1.0f, float dimension_v = 1.0f);
	virtual ~GridVAO() = default;

	DrawArraysConfig make_drawcall() const;

private:
	enum BindIdx : GLuint {
		general
	};

	std::unique_ptr<BufferObject> _vertex_data;
	GLsizei _count;
};