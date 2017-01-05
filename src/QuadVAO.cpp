#include "QuadVAO.h"

#include "Preamble.glsl"
#include <array>

QuadVAO::QuadVAO()
	: VAO()
	, _vertex_data(nullptr) {

	_vertex_data = std::make_unique<BufferObject>(GL_ARRAY_BUFFER);

	// Six times vec3 + vec2
	std::array<GLfloat, (3 + 2) * 6> packed_vertex_data{
		-.5, -.5, 0, 0, 0, 
		0.5, -.5, 0, 1, 0,
		0.5, 0.5, 0, 1, 1,
		-.5, -.5, 0, 0, 0,
		0.5, 0.5, 0, 1, 1,
		-.5, 0.5, 0, 0, 1
	};


	_vertex_data->buffer(packed_vertex_data.data(), packed_vertex_data.size() * sizeof(GLfloat), GL_STATIC_DRAW);

	{
		glVertexArrayVertexBuffer(id(), general, _vertex_data->id(), 0, (3+2) * sizeof(GLfloat));
		{
			const GLuint attrib_pos_vert(ATTRIBUTE_LOCATION_POSITION);
			glEnableVertexArrayAttrib(id(), attrib_pos_vert);
			glVertexArrayAttribFormat(id(), attrib_pos_vert, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat));
			glVertexArrayAttribBinding(id(), attrib_pos_vert, general);
		}

		{
			const GLuint attrib_pos_uv(ATTRIBUTE_LOCATION_TEXCOORD);
			glEnableVertexArrayAttrib(id(), attrib_pos_uv);
			glVertexArrayAttribFormat(id(), attrib_pos_uv, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
			glVertexArrayAttribBinding(id(), attrib_pos_uv, general);
		}
	}
}

const DrawArraysConfig QuadVAO::DRAW_CALL(GL_TRIANGLES, 6);