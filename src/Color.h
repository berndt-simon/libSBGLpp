#pragma once

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

namespace Color {
	glm::vec3 hsv_to_rgb(const glm::vec3& hsb);

	glm::vec3 rgb_to_hsv(const glm::vec3& rgb);

	void set_clearcolor(const glm::vec3& rgb);
	void set_clearcolor(const glm::vec4& rgba);
}


