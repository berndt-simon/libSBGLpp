#include "GridVAO.h"

#include "Preamble.glsl"
#include <vector>

GridVAO::GridVAO(unsigned divisions_u, unsigned divisions_v, float dimension_u, float dimension_v)
	: VAO()
	, _vertex_data(nullptr)
	, _count(0) {

	_vertex_data = std::make_unique<BufferObject>(GL_ARRAY_BUFFER);
	
	std::vector<GLfloat> packed_vertex_data;
	const size_t vert_cnt((2 * (divisions_u + 2)) + (2 * (divisions_v + 2)));
	packed_vertex_data.reserve(3 * vert_cnt);

	const float start_u(-dimension_u / 2);
	const float step_u(dimension_u / (divisions_u + 1));
	const float start_v(-dimension_v / 2);
	const float step_v(dimension_v / (divisions_v + 1));

	for (auto u(0); u < divisions_u + 2; ++u) {
		const auto x(start_u + (u * step_u));
		packed_vertex_data.push_back(x);
		packed_vertex_data.push_back(start_v);
		packed_vertex_data.push_back(0);

		packed_vertex_data.push_back(x);
		packed_vertex_data.push_back(-start_v);
		packed_vertex_data.push_back(0);
	}

	for (auto v(0); v < divisions_v + 2; ++v) {
		const auto y(start_v + (v * step_v));
		packed_vertex_data.push_back(start_u);
		packed_vertex_data.push_back(y);
		packed_vertex_data.push_back(0);

		packed_vertex_data.push_back(-start_u);
		packed_vertex_data.push_back(y);
		packed_vertex_data.push_back(0);
	}

	_vertex_data->buffer(packed_vertex_data.data(), packed_vertex_data.size() * sizeof(GLfloat), GL_STATIC_DRAW);
	_count = packed_vertex_data.size() / 3;

	{
		glVertexArrayVertexBuffer(id(), general, _vertex_data->id(), 0, 3 * sizeof(GLfloat));
		{
			const GLuint attrib_pos_vert(ATTRIBUTE_LOCATION_POSITION);
			glEnableVertexArrayAttrib(id(), attrib_pos_vert);
			glVertexArrayAttribFormat(id(), attrib_pos_vert, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat));
			glVertexArrayAttribBinding(id(), attrib_pos_vert, general);
		}
	}
}

DrawArraysConfig GridVAO::make_drawcall() const {
	return DrawArraysConfig(GL_LINES, _count);
}
