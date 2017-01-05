#pragma once

#include <stack>

#include <glm/mat4x4.hpp>
#include <GL/glew.h>


class MatrixStack : private std::stack<glm::mat4> {
public:
	class Backup {
	public:
		Backup(MatrixStack& parent);
		~Backup();
	private:
		MatrixStack& _parent;
	};

	MatrixStack();
	~MatrixStack() = default;

	void push();
	void pop();

	void identity();
	void load(const glm::mat4& mat);
	void pre_multiply(const glm::mat4& mat);
	void post_multiply(const glm::mat4& mat);

	void reset();

	operator const glm::mat4&() const;
	operator glm::mat4&();	

	MatrixStack& operator=(const glm::mat4& mat);

	void to_uniform(GLuint program, GLint location) const;

	const GLfloat* value_ptr() const;
};

