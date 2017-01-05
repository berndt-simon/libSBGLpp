#pragma once

#include <GL\glew.h>
#include "NoCopy.h"
#include <vector>

class FBO : private NoCopy {
public:
	FBO();
	~FBO();

	void blit_from(GLuint read_framebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const;
	void blit_from(GLuint read_framebuffer, GLint width, GLint height, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST) const;

	void blit_to(GLuint draw_framebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const;
	void blit_to(GLuint draw_framebuffer, GLint width, GLint height, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST) const;

	void attach_renderbuffer(GLenum attachment,  GLuint renderbuffer) const;
	void attach_texture(GLenum attachment, GLuint texture, GLint level) const;

	void draw_buffers(const std::vector<GLenum>& attachments) const;

	void bind() const;
	static void unbind();

	GLenum check(GLenum target = GL_FRAMEBUFFER) const;

private:


	GLuint _fbo_id;
};