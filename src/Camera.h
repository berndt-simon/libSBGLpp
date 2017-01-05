#pragma once

#include <glm\trigonometric.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

struct Projection {
	Projection(float width, float height, float near, float far);
	float width;
	float height;
	float near, far;

	virtual glm::mat4 make_projection_mat() const = 0;
	void update(float width, float height);
};

struct Ortho : Projection {
	Ortho();
	Ortho(float width, float height, float near = -0.5f, float far = 0.5f);
	glm::mat4 make_projection_mat() const override;
};

struct Perspective : Projection {
	explicit Perspective(float fov = glm::radians(60.0f));
	Perspective(float fov, float width, float height, float near = -0.5f, float far = 0.5f);
	float fov;
	glm::mat4 make_projection_mat() const override;
};

struct Camera {
	Camera();

	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 make_view_mat() const;
};