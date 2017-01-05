#pragma once

#include "Preamble.glsl"
#include <GL\gl.h>

#define LIGHT_UNIFORM_BLOCKBINDING 1
#define MATERIAL_UNIFORM_BLOCKBINDING 2

namespace BASIC_SHADER {

	namespace IMAGE_PLANE {
		static const char* VERTEX = R"(
#version 450

layout(location = 0) in vec3 in_vertex;
layout(location = 2) in vec2 in_uv;

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

out vec2 ex_uv;

void main() {
	gl_Position = vec4(in_vertex, 1);
	ex_uv = in_uv;
}
)";

			static const char* FRAGMENT = R"(
#version 450

layout(binding=0) uniform sampler2D uni_texture;

in vec2 ex_uv;
out vec4 out_color;

void main() {
  out_color = texture(uni_texture, ex_uv);
}
)";	
	}

	namespace UNLIT_TEXTURED {
		static const char* VERTEX = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(location = 0) in vec3 in_vertex;
layout(location = 2) in vec2 in_uv;

out Exchange {
	vec3 vec;
	vec2 uv;
} ex;

void main(void) {
	vec4 vertex = vec4(in_vertex, 1);

	ex.vec = (model_matrix * vertex).xyz;
	ex.uv = in_uv;

	gl_Position = model_view_projection_matrix * vertex;
}
)";

		static const char* FRAGMENT = R"(
#version 450

layout(binding=0) uniform sampler2D uni_texture;

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(location = 0) out vec4 out_color;
	
in Exchange {
	vec3 vec;
	vec2 uv;
} ex;
	
void main() {
	
	out_color = vec4(texture(uni_texture, ex.uv).rgb, 1);
}
)";
	}

	namespace LIT_TEXTURED {
		static const char* VERTEX = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(std140, binding = 1) uniform uni_light {
	vec3 light_position;
	vec3 light_intensities;
};

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

out Exchange {
	vec3 normal;
	vec3 vec;
	vec2 uv;
	vec3 eye_dir;
	vec3 light_dir;
} ex;

void main(void) {
	vec4 vertex = vec4(in_vertex, 1);

	ex.vec = (model_matrix * vertex).xyz;
	ex.uv = in_uv;

	vec3 vec_camspace = (view_matrix * model_matrix * vertex).xyz;
	ex.eye_dir = vec3(0, 0, 0) - vec_camspace;

	vec3 light_camspace = (view_matrix * vec4(light_position, 1)).xyz;
	ex.light_dir = light_camspace + ex.eye_dir;

	ex.normal = (view_matrix * transpose(inverse(model_matrix)) * vec4(in_normal, 0)).xyz;

	gl_Position = model_view_projection_matrix * vertex;
}
)";

		static const char* FRAGMENT = R"(
#version 450

layout(binding=0) uniform sampler2D uni_texture;

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(std140, binding = 1) uniform uni_light {
	vec3 light_position;
	vec3 light_intensities;
};

layout(std140, binding = 2) uniform uni_material {
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
};

layout(location = 0) out vec4 out_color;
	
in Exchange {
	vec3 normal;
	vec3 vec;
	vec2 uv;
	vec3 eye_dir;
	vec3 light_dir;
} ex;
	
void main() {
	
	float distance = length(light_position - ex.vec);

	vec3 normal = normalize(ex.normal);
	vec3 light = normalize(ex.light_dir);

	float cos_theta = clamp(dot(normal, light), 0, 1);

	vec3 eye = normalize(ex.eye_dir);

	vec3 reflection = reflect(-light, normal);

	float cos_alpha = clamp(dot(eye, reflection), 0, 1);

	out_color = vec4(
		ambient_color + 
		(texture(uni_texture, ex.uv).rgb * light_intensities * cos_theta / (distance * distance))  +
		(specular_color * light_intensities * pow(cos_alpha, 5) / (distance * distance))
		, 1);

}
)";
	}

	namespace UNLIT_SOLID {
		static const char* VERTEX = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(location = 0) in vec3 in_vertex;

void main(void) {
	vec4 vertex = vec4(in_vertex, 1);

	gl_Position = model_view_projection_matrix * vertex;
}
)";

		static const char* FRAGMENT = R"(
#version 450

layout(std140, binding = 2) uniform uni_material {
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
};

layout(location = 0) out vec4 out_color;
		
void main() {
	out_color = vec4(ambient_color, 1);
}
)";
	}

	namespace LIT_SOLID {
		static const char* VERTEX = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(std140, binding = 1) uniform uni_light {
	vec3 light_position;
	vec3 light_intensities;
};

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;

out Exchange {
	vec3 normal;
	vec3 vec;
	vec3 eye_dir;
	vec3 light_dir;
} ex;

void main(void) {
	vec4 vertex = vec4(in_vertex, 1);

	ex.vec = (model_matrix * vertex).xyz;

	vec3 vec_camspace = (view_matrix * model_matrix * vertex).xyz;
	ex.eye_dir = vec3(0, 0, 0) - vec_camspace;

	vec3 light_camspace = (view_matrix * vec4(light_position, 1)).xyz;
	ex.light_dir = light_camspace + ex.eye_dir;

	ex.normal = (view_matrix * transpose(inverse(model_matrix)) * vec4(in_normal, 0)).xyz;

	gl_Position = model_view_projection_matrix * vertex;
}
)";

		static const char* FRAGMENT = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(std140, binding = 1) uniform uni_light {
	vec3 light_position;
	vec3 light_intensities;
};

layout(std140, binding = 2) uniform uni_material {
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
};

layout(location = 0) out vec4 out_color;
	
in Exchange {
	vec3 normal;
	vec3 vec;
	vec3 eye_dir;
	vec3 light_dir;
} ex;
	
void main() {
	
	float distance = length(light_position - ex.vec);

	vec3 normal = normalize(ex.normal);
	vec3 light = normalize(ex.light_dir);

	float cos_theta = clamp(dot(normal, light), 0, 1);

	vec3 eye = normalize(ex.eye_dir);

	vec3 reflection = reflect(-light, normal);

	float cos_alpha = clamp(dot(eye, reflection), 0, 1);

	out_color = vec4(
		ambient_color + 
		(diffuse_color * light_intensities * cos_theta / (distance * distance))  +
		(specular_color * light_intensities * pow(cos_alpha, 5) / (distance * distance))
		, 1);
}
)";
	}
}

