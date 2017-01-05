#pragma once

#include <iosfwd>
#include <vector>
#include <string>

#include <memory>

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

#include "VAO.h"
#include "DrawCall.h"
#include "BufferObject.h"



class TriangleMesh {
public:
	TriangleMesh() = default;
	~TriangleMesh() = default;

	auto& vertices() {
		return _vertices;
	};
	const auto& vertices() const {
		return _vertices;
	};

	auto& normals() {
		return _normals;
	};
	const auto& normals() const {
		return _normals;
	};
	bool has_normals() const;

	auto& texture_coordinates() {
		return _texture_coordinates;
	};
	const auto& texture_coordinates() const {
		return _texture_coordinates;
	};
	bool has_texture_coordinates() const;

	auto& faces() {
		return _faces;
	};
	const auto& faces() const {
		return _faces;
	};

	bool validate() const;

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texture_coordinates;

	std::vector<glm::uvec3> _faces;
};

class TriangleMeshVAO : public VAO {
public:

	explicit TriangleMeshVAO(const TriangleMesh& mesh);
	virtual ~TriangleMeshVAO() = default;

	DrawElementsConfig make_drawcall() const;

private:

	enum BindIdx : GLuint {
		general
	};

	std::unique_ptr<BufferObject> _vertex_data;
	std::unique_ptr<BufferObject> _index_data;

	GLsizei _count;
};
