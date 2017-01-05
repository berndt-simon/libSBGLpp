#include "FBO.h"

FBO::FBO() 
	: _fbo_id(0) {
	glCreateFramebuffers(1, &_fbo_id);
}

FBO::~FBO() {
	if (glIsFramebuffer(_fbo_id)) {
		glDeleteFramebuffers(1, &_fbo_id);
	}
}

void FBO::blit_from(GLuint read_framebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
	glBlitNamedFramebuffer(read_framebuffer, _fbo_id, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void FBO::blit_from(GLuint read_framebuffer, GLint width, GLint height, GLbitfield mask, GLenum filter) const {
	blit_from(read_framebuffer, 0, 0, width, height, 0, 0, width, height, mask, filter);
}

void FBO::blit_to(GLuint draw_framebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
	glBlitNamedFramebuffer(_fbo_id, draw_framebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void FBO::blit_to(GLuint draw_framebuffer, GLint width, GLint height, GLbitfield mask, GLenum filter) const {
	blit_to(draw_framebuffer, 0, 0, width, height, 0, 0, width, height, mask, filter);
}

void FBO::attach_renderbuffer(GLenum attachment, GLuint renderbuffer) const {
	glNamedFramebufferRenderbuffer(_fbo_id, attachment, GL_RENDERBUFFER, renderbuffer);
}

void FBO::attach_texture(GLenum attachment, GLuint texture, GLint level) const {
	glNamedFramebufferTexture(_fbo_id, attachment, texture, level);
}

void FBO::draw_buffers(const std::vector<GLenum>& attachments) const {
	glNamedFramebufferDrawBuffers(_fbo_id, attachments.size(), attachments.data());
}


void FBO::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
}

void FBO::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLenum FBO::check(GLenum target) const {
	return glCheckNamedFramebufferStatus(_fbo_id, target);
}
