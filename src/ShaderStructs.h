#pragma once

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

struct uni_lights_t {
	alignas(16) glm::vec3 light_position;
	alignas(16) glm::vec3 light_intensities;
};

struct uni_matrices_t {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 model_view_projection;
};

struct uni_material_t {
	alignas(16) glm::vec3 ambient_color;
	alignas(16) glm::vec3 diffuse_color;
	alignas(16) glm::vec3 specular_color;
};