#include "TriangleMesh.h"

#include <stdexcept>
#include <glm\common.hpp>

#include "Preamble.glsl"


#pragma warning(disable : 4267)

bool TriangleMesh::has_normals() const {
	return !_normals.empty();
}

bool TriangleMesh::has_texture_coordinates() const {
	return !_texture_coordinates.empty();
}

bool TriangleMesh::validate() const {
	const glm::uvec3 vert_cnt(_vertices.size());
	for (const auto& face : _faces) {
		if (glm::any(glm::greaterThanEqual(face, vert_cnt))) {
			return false;
		}
	}
	if (has_normals()) {
		if (_vertices.size() != _normals.size()) {
			return false;
		}
	}
	if (has_texture_coordinates()) {
		if (_vertices.size() != _texture_coordinates.size()) {
			return false;
		}
	}
	return true;
}

static GLsizei calc_stride(const TriangleMesh& mesh) {
	GLsizei stride(0);
	stride += 3 * sizeof(GLfloat);	// Position = vec3
	if (mesh.has_normals()) {
		stride += 3 * sizeof(GLfloat); // Normals = vec3;
	}
	if (mesh.has_texture_coordinates()) {
		stride += 2 * sizeof(GLfloat); // UVs = vec2;
	}
	return stride;
}

static void push_back(std::vector<GLfloat>& data, const glm::vec2& vec) {
	data.push_back(vec.x);
	data.push_back(vec.y);
}

static void push_back(std::vector<GLfloat>& data, const glm::vec3& vec) {
	data.push_back(vec.x);
	data.push_back(vec.y);
	data.push_back(vec.z);
}

static void push_back(std::vector<GLuint>& data, const glm::uvec3& vec) {
	data.push_back(vec.x);
	data.push_back(vec.y);
	data.push_back(vec.z);
}

static void pack_vertex_data(const TriangleMesh& mesh, std::vector<GLfloat>& vertex_data) {
	for (auto i(0U); i < mesh.vertices().size(); ++i) {
		push_back(vertex_data, mesh.vertices()[i]);
		if (mesh.has_texture_coordinates()) {
			push_back(vertex_data, mesh.texture_coordinates()[i]);
		}
		if (mesh.has_normals()) {
			push_back(vertex_data, mesh.normals()[i]);
		}
	}
}

static void pack_index_data(const TriangleMesh& mesh, std::vector<GLuint>& index_data) {
	for (auto i(0U); i < mesh.faces().size(); ++i) {
		push_back(index_data, mesh.faces()[i]);
	}
}

TriangleMeshVAO::TriangleMeshVAO(const TriangleMesh& mesh)
	: VAO()
	, _count(0)
	, _vertex_data(nullptr)
	, _index_data(nullptr) {

	if (!mesh.validate()) {
		throw std::runtime_error("Mesh-Verification failed!");
	}

	_vertex_data = std::make_unique<BufferObject>(GL_ARRAY_BUFFER);
	_index_data = std::make_unique<BufferObject>(GL_ELEMENT_ARRAY_BUFFER);

	std::vector<GLfloat> packed_vertex_data;
	pack_vertex_data(mesh, packed_vertex_data);

	std::vector<GLuint> packed_index_data;
	pack_index_data(mesh, packed_index_data);

	_vertex_data->buffer(packed_vertex_data.data(), packed_vertex_data.size() * sizeof(GLfloat), GL_STATIC_DRAW);
	_index_data->buffer(packed_index_data.data(), packed_index_data.size() * sizeof(GLuint), GL_STATIC_DRAW);


	{
		glVertexArrayVertexBuffer(id(), general, _vertex_data->id(), 0, calc_stride(mesh));
		GLuint offset(0);

		{
			const GLuint attrib_pos_vert(ATTRIBUTE_LOCATION_POSITION);
			glEnableVertexArrayAttrib(id(), attrib_pos_vert);
			glVertexArrayAttribFormat(id(), attrib_pos_vert, 3, GL_FLOAT, GL_FALSE, offset);
			glVertexArrayAttribBinding(id(), attrib_pos_vert, general);
			offset += 3 * sizeof(GLfloat);
		}

		if (mesh.has_texture_coordinates()) {
			const GLuint attrib_pos_uv(ATTRIBUTE_LOCATION_TEXCOORD);
			glEnableVertexArrayAttrib(id(), attrib_pos_uv);
			glVertexArrayAttribFormat(id(), attrib_pos_uv, 2, GL_FLOAT, GL_FALSE, offset);
			glVertexArrayAttribBinding(id(), attrib_pos_uv, general);
			offset += 2 * sizeof(GLfloat);
		}

		if (mesh.has_normals()) {
			const GLuint attrib_pos_normal(ATTRIBUTE_LOCATION_NORMAL);
			glEnableVertexArrayAttrib(id(), attrib_pos_normal);
			glVertexArrayAttribFormat(id(), attrib_pos_normal, 3, GL_FLOAT, GL_FALSE, offset);
			glVertexArrayAttribBinding(id(), attrib_pos_normal, general);
			offset += 3 * sizeof(GLfloat);
		}
	}

	glVertexArrayElementBuffer(id(), _index_data->id());

	_count = mesh.faces().size() * 3;
}

DrawElementsConfig TriangleMeshVAO::make_drawcall() const {
	return DrawElementsConfig(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
}
