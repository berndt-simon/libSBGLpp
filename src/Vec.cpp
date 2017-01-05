#include "Vec.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, const glm::vec2& v) {
	return os << v.x << "," << v.y;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
	return os << v.x << "," << v.y << "," << v.z;
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
	return os << v.x << "," << v.y << "," << v.z << "," << v.w;
}