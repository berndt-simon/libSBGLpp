#include "GBuffer.h"
#include <stdexcept>

#pragma warning(disable : 4267)

GBuffer::GBuffer(GLuint width, GLuint height) {

	glCreateFramebuffers(1, &_fbo_id); 
	glCreateTextures(GL_TEXTURE_2D, _textures.size(), _textures.data());
	glCreateTextures(GL_TEXTURE_2D, 1, &_depth_texture);

	for (auto i(0U); i < _textures.size(); ++i) {
		glTextureStorage2D(_textures[i], 0, GL_RGB32F, width, height);
		glNamedFramebufferTexture(_fbo_id, GL_COLOR_ATTACHMENT0 + i, _textures[i], 0);
	}

	glTextureStorage2D(_depth_texture, 0, GL_DEPTH_COMPONENT32F, width, height);
	glNamedFramebufferTexture(_fbo_id, GL_DEPTH_ATTACHMENT, _depth_texture, 0);

	std::array<GLenum, 4> draw_buffers{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glNamedFramebufferDrawBuffers(_fbo_id, draw_buffers.size(), draw_buffers.data());

	if (glCheckNamedFramebufferStatus(_fbo_id, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("FB-Error");
	}
}

GBuffer::~GBuffer() {
	if (glIsFramebuffer(_fbo_id)) {
		glDeleteFramebuffers(1, &_fbo_id);
	}

	for (const auto& texture : _textures) {
		if (glIsTexture(texture)) {
			glDeleteTextures(1, &texture);
		}
	}
	if (glIsTexture(_depth_texture)) {
		glDeleteTextures(1, &_depth_texture);
	}
}

void GBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
}

void GBuffer::bind_for_writing() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo_id);
}

void GBuffer::bind_for_reading() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo_id);
}

void GBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::default_width(GLint width) {
	if (width < 0 || width > GL_MAX_FRAMEBUFFER_WIDTH) {
		throw std::invalid_argument("Invalid Width");
	}
	glNamedFramebufferParameteri(_fbo_id, GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
}

void GBuffer::default_height(GLint height) {
	if (height < 0 || height > GL_MAX_FRAMEBUFFER_HEIGHT) {
		throw std::invalid_argument("Invalid Height");
	}
	glNamedFramebufferParameteri(_fbo_id, GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
}

void GBuffer::default_layers(GLint layers) {
	if (layers < 0 || layers > GL_MAX_FRAMEBUFFER_LAYERS) {
		throw std::invalid_argument("Invalid Layers");
	}
	glNamedFramebufferParameteri(_fbo_id, GL_FRAMEBUFFER_DEFAULT_LAYERS, layers);
}

void GBuffer::default_samples(GLint samples) {
	if (samples < 0 || samples > GL_MAX_FRAMEBUFFER_SAMPLES) {
		throw std::invalid_argument("Invalid Samples");
	}
	glNamedFramebufferParameteri(_fbo_id, GL_FRAMEBUFFER_DEFAULT_SAMPLES, samples);
}

void GBuffer::default_fixed_sample_locations(GLint sample_location) {
	glNamedFramebufferParameteri(_fbo_id, GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, sample_location);
}
