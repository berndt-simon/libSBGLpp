#pragma once

#include <GL/glew.h>

struct DrawCall {
	virtual void execute() const = 0;

	GLenum mode;
	GLsizei count;

	DrawCall(GLenum mode, GLsizei count)
		: mode(mode)
		, count(count) {
	};
};

struct DrawArraysConfig;
struct DrawElementsConfig;
struct DrawElementsInstancedConfig;
struct DrawArraysInstancedConfig;

struct DrawArraysConfig : DrawCall {
	DrawArraysConfig(GLenum mode, GLsizei count, GLint first = 0)
		: DrawCall(mode, count)
		, first(first) {
	};

	void execute() const override;

	DrawArraysInstancedConfig to_instanced() const;

	GLint first;
};

struct DrawElementsConfig : DrawCall {
	DrawElementsConfig(GLenum mode, GLsizei count, GLenum type = GL_UNSIGNED_INT, void* indices = 0)
		: DrawCall(mode, count)
		, type(type)
		, indices(indices) {
	};

	void execute() const override;

	DrawElementsInstancedConfig to_instanced() const;

	GLenum type;
	void* indices;
};

struct DrawInstancedConfig : DrawCall {
	DrawInstancedConfig(GLenum mode, GLsizei count, GLsizei primCount)
		: DrawCall(mode, count)
		, primCount(primCount) {
	};

	GLsizei primCount;
};

struct DrawArraysInstancedConfig : DrawInstancedConfig {
	DrawArraysInstancedConfig(GLenum mode, GLsizei count, GLsizei primCount, GLint first = 0)
		: DrawInstancedConfig(mode, count, primCount)
		, first(first) {
	};

	void execute() const override;

	DrawArraysConfig to_single() const;

	GLint first;
};

struct DrawElementsInstancedConfig : DrawInstancedConfig {
	DrawElementsInstancedConfig(GLenum mode, GLsizei count, GLsizei primCount, GLenum type = GL_UNSIGNED_INT, void* indices = 0)
		: DrawInstancedConfig(mode, count, primCount)
		, type(type)
		, indices(indices) {
	};

	void execute() const override;

	DrawElementsConfig to_single() const;

	GLenum type;
	void* indices;
};