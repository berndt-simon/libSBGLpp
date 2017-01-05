#include "Color.h"

#include <GL\glew.h>
#include <glm\common.hpp>
#include <glm\gtx\component_wise.hpp>

glm::vec3 Color::hsv_to_rgb(const glm::vec3& hsv) {
	glm::vec3 out;

	float p, q, t, ff;
	long i;

	if (hsv[1] == 0.0f) {
		out.r = hsv[2];
		out.g = hsv[2];
		out.b = hsv[2];
		return out;
	}

	float hh(hsv[0]);
	if (hh == 360.0f) {
		hh = 0.0f;
	}
	hh /= 60.0f;
	i = hh;
	ff = hh - i;
	p = hsv[2] * (1.0f - hsv[1]);
	q = hsv[2] * (1.0f - (hsv[1] * ff));
	t = hsv[2] * (1.0f - (hsv[1] * (1.0f - ff)));

	switch (i) {
		case 0:
			out.r = hsv[2];
			out.g = t;
			out.b = p;
			break;
		case 1:
			out.r = q;
			out.g = hsv[2];
			out.b = p;
			break;
		case 2:
			out.r = p;
			out.g = hsv[2];
			out.b = t;
			break;
		case 3:
			out.r = p;
			out.g = q;
			out.b = hsv[2];
			break;
		case 4:
			out.r = t;
			out.g = p;
			out.b = hsv[2];
			break;
		case 5:
		default:
			out.r = hsv[2];
			out.g = p;
			out.b = q;
			break;
	}
	return out;
}

glm::vec3 Color::rgb_to_hsv(const glm::vec3& color) {
	glm::vec3 out;
	double delta;

	const float min(glm::compMin(color));
	const float max(glm::compMax(color));

	out[2] = max;
	delta = max - min;
	if (delta < 0.00001f) {
		out[1] = 0;
		out[0] = 0;
		return out;
	}
	if (max > 0.0) {
		out[1] = delta / max;
	} else {
		out[1] = 0.0;
		out[0] = 0.0;
		return out;
	}
	if (color.r == max) {
		out[0] = (color.g - color.b) / delta;
	} else if (color.g == max) {
		out[0] = 2.0 + (color.b - color.r) / delta;
	} else {
		out[0] = 4.0 + (color.r - color.g) / delta;
	}
	out[0] *= 60.0;

	if (out[0] < 0.0) {
		out[0] += 360.0;
	}

	return out;
}

void Color::set_clearcolor(const glm::vec3& rgb) {
	glClearColor(rgb.r, rgb.b, rgb.b, 1);
}

void Color::set_clearcolor(const glm::vec4& rgba) {
	glClearColor(rgba.r, rgba.b, rgba.b, rgba.a);
}
