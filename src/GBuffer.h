#pragma once
#include "NoCopy.h"
#include <array>
#include <GL/glew.h>

class GBuffer : private NoCopy {
public:

	enum TextureType {
		diffuse, position, normal, texture_coordinate
	};

	GBuffer(GLuint width, GLuint height);
	virtual ~GBuffer();

	void bind();
	void bind_for_writing();
	void bind_for_reading();

	static void unbind();

protected:
	void default_width(GLint width);
	void default_height(GLint height);
	void default_layers(GLint layers);
	void default_samples(GLint samples);
	void default_fixed_sample_locations(GLint sample_location);

private:
	GLuint _fbo_id;
	std::array<GLuint, 4> _textures;
	GLuint _depth_texture;

};