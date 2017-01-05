#pragma once

#include "Preamble.glsl"

namespace DEBUG_SHADER {

	namespace FLAT_UVCOORDS {
		static const char* VERTEX = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(location = 0) in vec3 in_vertex;
layout(location = 2) in vec2 in_uv;

out vec2 ex_uv;

void main(void) {
	gl_Position = model_view_projection_matrix * vec4(in_vertex, 1);

	ex_uv = in_uv;
}
)";

		static const char* FRAGMENT = R"(
#version 450

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

layout(location = 0) out vec4 out_color;
	
in vec2 ex_uv;
	
void main() {
	
	out_color = vec4(ex_uv, 1, 1);
}
)";	
	}

	namespace DRAW_NORMALS {
		static const char* VERTEX = R"(
#version 450

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;

out Exchange {
	vec4 normal;
	vec4 color;
} ex;

void main() {
  gl_Position = vec4(in_vertex, 1);
  ex.normal = vec4(in_normal, 0);
  ex.color =  vec4(1, 1, 0, 1);
}
)";

		static const char* GEOMETRY = R"(
#version 450

layout(triangles) in;
layout(line_strip, max_vertices=6) out;

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

in Exchange {
	vec4 normal;
	vec4 color;
} ex[];

uniform float normal_length = 1;

out vec4 ex_color;

void main() {
  int i;
  for(i=0; i < gl_in.length(); ++i) {
    vec3 pos = gl_in[i].gl_Position.xyz;
    vec3 norm = ex[i].normal.xyz;
    
    gl_Position = model_view_projection_matrix * vec4(pos, 1);
    ex_color = ex[i].color;
    EmitVertex();
    
    gl_Position = model_view_projection_matrix * vec4(pos + norm * normal_length, 1.0);
    ex_color = ex[i].color;
    EmitVertex();
    
    EndPrimitive();
  }
}
)";

		static const char* FRAGMENT = R"(
#version 450

in vec4 ex_color;
out vec4 out_color;

void main() {
  out_color = ex_color;
}
)";
	}


	namespace DRAW_AXIS {
		static const char* VERTEX = R"(
#version 450

layout(location = 0) in vec3 in_vertex;

void main() {
  gl_Position = vec4(in_vertex, 1);
  ex.color =  vec4(1, 1, 1, 1);
}
)";

		static const char* GEOMETRY = R"(
#version 450

layout(points) in;
layout(line_strip, max_vertices=6) out;

layout(std140, binding = 0) uniform uni_matrices {
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 model_view_projection_matrix;
};

uniform float axis_length = 1;

out vec4 ex_color;

void main() {
  int i;
  for(i=0; i < gl_in.length(); ++i) {
    vec4 pos_0 = gl_in[i].gl_Position;
	vec4 pos_x = pos_0 + (model_matrix * vec4(axis_length, 0, 0, 1));
	vec4 pos_y = pos_0 + (model_matrix * vec4(0, axis_length, 0, 1));
	vec4 pos_z = pos_0 + (model_matrix * vec4(0, 0, axis_length, 1))
    
    gl_Position = model_view_projection_matrix * pos_0;
    ex_color = vec4(1, 0, 0, 1);
    EmitVertex();
	gl_Position = model_view_projection_matrix * pos_x;
    ex_color = vec4(1, 0, 0, 1);
    EmitVertex();
	EndPrimitive();

    gl_Position = model_view_projection_matrix * pos_0;
    ex_color = vec4(0, 1, 0, 1);
    EmitVertex();
	gl_Position = model_view_projection_matrix * pos_y;
    ex_color = vec4(0, 1, 0, 1);
    EmitVertex();
	EndPrimitive();

	gl_Position = model_view_projection_matrix * pos_0;
    ex_color = vec4(0, 0, 1, 1);
    EmitVertex();
	gl_Position = model_view_projection_matrix * pos_z;
    ex_color = vec4(0, 0, 1, 1);
    EmitVertex();
	EndPrimitive();    
  }
}
)";

		static const char* FRAGMENT = R"(
#version 450

in vec4 ex_color;
out vec4 out_color;

void main() {
  out_color = ex_color;
}
)";
	
	
	}


	namespace UV_MAP {
		static const char* VERTEX = R"(
#version 450

layout(location = 2) in vec2 in_uv;

void main() {
  gl_Position = vec4(in_uv, 0, 1);
}
)";
	
		static const char* FRAGMENT = R"(
#version 450

uniform vec4 uni_uv_color = vec4(1, 1, 1, 1);
out vec4 out_color;

void main() {
  out_color = uni_uv_color;
}
)";
	
	}

}