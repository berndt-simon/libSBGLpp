#include "Camera.h"

#include <glm\vec4.hpp>
#include <glm\gtc\matrix_transform.hpp>

Projection::Projection(float width, float height, float near, float far)
	: width(width)
	, height(height)
	, near(near)
	, far(far) {
}

Ortho::Ortho()
	: Projection(1, 1, -0.5, 0.5) {
}

Ortho::Ortho(float width, float height, float near, float far)
	: Projection(width, height, near, far) {
}

glm::mat4 Ortho::make_projection_mat() const {
	return glm::ortho(-width / 2, width / 2, height / 2, -height / 2, near, far);
}

Perspective::Perspective(float fov)
	: Perspective(fov, 1, 1, 0.1f, 10.0f) {
}

Perspective::Perspective(float fov, float width, float height, float near, float far)
	: Projection(width, height, near, far)
	, fov(fov) {
}

glm::mat4 Perspective::make_projection_mat() const {
	return glm::perspectiveFov(fov, width, height, near, far);
}

Camera::Camera()
	: pos(0, 0, 0)
	, target(0, 0, 1)
	, up(0, 1, 0) {
}

glm::mat4 Camera::make_view_mat() const {
	return glm::lookAt(pos, target, up);
}

void Projection::update(float width, float height) {
	this->width = width;
	this->height = height;
}
