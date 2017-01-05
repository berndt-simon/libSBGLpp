#include "ObjLoader.h"

#include <sstream>
#include <istream>

#include <tuple>
#include <stdexcept>
#include <glm\common.hpp>
#include <glm\gtc\matrix_inverse.hpp>

#include <set>

const std::string ObjLoader::IDENTIFIER_VERTEX("v");
const std::string ObjLoader::IDENTIFIER_UV("vt");
const std::string ObjLoader::IDENTIFIER_NORMAL("vn");
const std::string ObjLoader::IDENTIFIER_FACE("f");
const char ObjLoader::LINE_INTERNAL_DELIMITER(' ');
const char ObjLoader::FACE_INTERNAL_DELIMITER('/');


static void split(const std::string& input, char delimiter, std::vector<std::string>& output) {
	std::istringstream input_stream(input);
	std::string token;
	while (std::getline(input_stream, token, delimiter)) {
		output.push_back(token);
	}
}

std::unique_ptr<ObjMesh> ObjLoader::load(std::istream& in) const {
	auto mesh = std::make_unique<ObjMesh>();

	std::string line;
	while (std::getline(in, line)) {
		std::vector<std::string> tokens;
		split(line, LINE_INTERNAL_DELIMITER, tokens);
		if (tokens[0] == IDENTIFIER_VERTEX) {
			if (tokens.size() == 4) {
				mesh->vertices().emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), 1.0f);
			} else if (tokens.size() == 5) {
				mesh->vertices().emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]));
			} else {
				throw std::runtime_error("OBJ Vertex Identifier needs 3 or 4 Arguments");
			}
		} else if (tokens[0] == IDENTIFIER_UV) {
			if (tokens.size() == 2) {
				mesh->texture_coordinates().emplace_back(std::stof(tokens[1]), 0.0f, 0.0f);
			} else if (tokens.size() == 3) {
				mesh->texture_coordinates().emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), 0.0f);
			} else if (tokens.size() == 4) {
				mesh->texture_coordinates().emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			} else {
				throw std::runtime_error("OBJ UV Identifier needs at 1, 2 or 3 Arguments");
			}
		} else if (tokens[0] == IDENTIFIER_NORMAL) {
			if (tokens.size() == 4) {
				mesh->normals().emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			} else {
				throw std::runtime_error("OBJ Normal Identifier needs 3 Arguments");
			}
		} else if (tokens[0] == IDENTIFIER_FACE) {
			if (tokens.size() == 4) {
				Triangle_t triangle{};
				for (auto i(0U); i < 3; ++i) {
					std::vector<std::string> components;
					split(tokens[i + 1], FACE_INTERNAL_DELIMITER, components);
					if (components.size() == 3) {
						triangle.normal_indices[i] = std::stoi(components[2]) - 1;
					}
					if (components.size() >= 2) {
						if (!components[1].empty()) {
							triangle.uv_indices[i] = std::stoi(components[1]) - 1;
						}
					}
					if (components.size() >= 1) {
						triangle.vertex_idices[i] = std::stoi(components[0]) - 1;
					}
				}
				mesh->faces().push_back(triangle);
			} else {
				throw std::runtime_error("OBJ Face Identifier needs 3 Arguments");
			}
		}
	}

	for (auto& vertex : mesh->vertices()) {
		vertex = _global_transform * vertex;
	}

	/*if (mesh->has_normals()) {
		const auto transposed_inverse = glm::inverseTranspose(_global_transform);
		for (auto& normal : mesh->normals()) {
			normal = glm::vec3(transposed_inverse * glm::vec4(normal, 0.0f));
		}
	}*/

	return mesh;
}

bool ObjMesh::has_normals() const {
	return !_normals.empty();
}

bool ObjMesh::has_texture_coordinates() const {
	return !_texture_coordinates.empty();
}

bool ObjMesh::validate() const {
	const glm::uvec3 vert_cnt(_vertices.size());
	const glm::uvec3 normal_cnt(_normals.size());
	const glm::uvec3 uv_cnt(_texture_coordinates.size());

	for (const auto& face : _faces) {
		if (glm::any(glm::greaterThanEqual(face.vertex_idices, vert_cnt))) {
			return false;
		}
		if (has_normals()) {
			if (glm::any(glm::greaterThanEqual(face.normal_indices, normal_cnt))) {
				return false;
			}
		}
		if (has_texture_coordinates()) {
			if (glm::any(glm::greaterThanEqual(face.uv_indices, uv_cnt))) {
				return false;
			}
		}
	}
	return true;
}

bool ObjMesh::is_trimesh_compatible() const {
	if (has_normals() || has_texture_coordinates()) {
		for (const auto& face : _faces) {
			if (has_normals() && face.vertex_idices != face.normal_indices) {
				return false;
			}
			if (has_texture_coordinates() && face.vertex_idices != face.uv_indices) {
				return false;
			}
		}
	}
	return true;
}

void ObjMesh::direct_transfer(TriangleMesh& tri_mesh) const {
	for (const auto& face : _faces) {
		tri_mesh.faces().push_back(face.vertex_idices);
	}
	for (const auto& vertex : _vertices) {
		tri_mesh.vertices().emplace_back(vertex.x, vertex.y, vertex.z);
	}
	if (has_normals()) {
		for (const auto& normal : _normals) {
			tri_mesh.normals().emplace_back(normal.x, normal.y, normal.z);
		}
	}
	if (has_texture_coordinates()) {
		for (const auto& texture_coordinate : _texture_coordinates) {
			tri_mesh.texture_coordinates().emplace_back(texture_coordinate.x, texture_coordinate.y);
		}
	}
}

void ObjMesh::convert_transfer(TriangleMesh& tri_mesh) const {
	std::set<TriangleComp_t> unique_vertices;

	for (const auto& face : _faces) {
		unique_vertices.insert(TriangleComp_t{ face.vertex_idices.x, face.uv_indices.x, face.normal_indices.x });
		unique_vertices.insert(TriangleComp_t{ face.vertex_idices.y, face.uv_indices.y, face.normal_indices.y });
		unique_vertices.insert(TriangleComp_t{ face.vertex_idices.z, face.uv_indices.z, face.normal_indices.z });
	}

#pragma region reserve
	tri_mesh.vertices().reserve(unique_vertices.size());
	if (has_texture_coordinates()) {
		tri_mesh.texture_coordinates().reserve(unique_vertices.size());
	}
	if (has_normals()) {
		tri_mesh.normals().reserve(unique_vertices.size());
	}
#pragma endregion	

	for (const auto& unique_vertex : unique_vertices) {
		const auto& vertex(_vertices[unique_vertex.vertex_idx]);
		tri_mesh.vertices().emplace_back(vertex.x, vertex.y, vertex.z);
		if (has_texture_coordinates()) {
			const auto& uv(_texture_coordinates[unique_vertex.uv_idx]);
			tri_mesh.texture_coordinates().emplace_back(uv.x, uv.y);
		}
		if (has_normals()) {
			const auto& normal(_normals[unique_vertex.normal_idx]);
			tri_mesh.normals().emplace_back(normal.x, normal.y, normal.z);
		}
	}

	for (const auto& face : _faces) {
		const TriangleComp_t v0{ face.vertex_idices.x, face.uv_indices.x, face.normal_indices.x };
		const auto idx0 = std::distance(unique_vertices.begin(), unique_vertices.find(v0));

		const TriangleComp_t v1{ face.vertex_idices.y, face.uv_indices.y, face.normal_indices.y };
		const auto idx1 = std::distance(unique_vertices.begin(), unique_vertices.find(v1));

		const TriangleComp_t v2{ face.vertex_idices.z, face.uv_indices.z, face.normal_indices.z };
		const auto idx2 = std::distance(unique_vertices.begin(), unique_vertices.find(v2));

		tri_mesh.faces().emplace_back(idx0, idx1, idx2);
	}

}

std::unique_ptr<TriangleMesh> ObjMesh::to_trianglemesh() const {
	if (!validate()) {
		throw std::runtime_error("Mesh-Validation Failed!");
	}

	auto tri_mesh = std::make_unique<TriangleMesh>();
	if (is_trimesh_compatible()) {
		direct_transfer(*tri_mesh);
	} else {
		convert_transfer(*tri_mesh);
	}

	return tri_mesh;
}

bool std::operator<(const TriangleComp_t& lhs, const TriangleComp_t& rhs) {
	return std::tie(lhs.vertex_idx, lhs.uv_idx, lhs.normal_idx) < std::tie(rhs.vertex_idx, rhs.uv_idx, rhs.normal_idx);
}

