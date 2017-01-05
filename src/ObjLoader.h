#pragma once

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

#include <glm\mat4x4.hpp>

#include <memory>
#include <string>

#include "TriangleMesh.h"

struct Triangle_t {
	glm::uvec3 vertex_idices;
	glm::uvec3 uv_indices;
	glm::uvec3 normal_indices;
};

struct TriangleComp_t {
	unsigned vertex_idx;
	unsigned uv_idx;
	unsigned normal_idx;
};
 
namespace std {
	bool operator<(const TriangleComp_t& lhs, const TriangleComp_t& rhs);
}

class ObjMesh {
public:
	ObjMesh() = default;
	~ObjMesh() = default;

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


	std::unique_ptr<TriangleMesh> to_trianglemesh() const;

private:
	bool is_trimesh_compatible() const;

	void direct_transfer(TriangleMesh& tri_mesh) const;
	void convert_transfer(TriangleMesh& tri_mesh) const;

	std::vector<glm::vec4> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec3> _texture_coordinates;

	std::vector<Triangle_t> _faces;
};

class ObjLoader {
public:
	ObjLoader() 
		: _global_transform(1.0f) {
	};
	~ObjLoader() = default;

	glm::mat4& transform() {
		return _global_transform;
	}
	const glm::mat4& transform() const {
		return _global_transform;
	}

	std::unique_ptr<ObjMesh> load(std::istream& in) const;

private:
	static const std::string IDENTIFIER_VERTEX;
	static const std::string IDENTIFIER_UV;
	static const std::string IDENTIFIER_NORMAL;
	static const std::string IDENTIFIER_FACE;
	static const char LINE_INTERNAL_DELIMITER;
	static const char FACE_INTERNAL_DELIMITER;

	glm::mat4 _global_transform;

};