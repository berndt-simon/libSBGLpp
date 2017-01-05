#include "MatrixStack.h"

#include <glm/gtc/type_ptr.hpp>


MatrixStack::MatrixStack() {
	stack::push(glm::mat4(1.0f));
}

void MatrixStack::push() {
	stack::push(stack::top());
}

void MatrixStack::pop() {
	stack::pop();
	// Always keep an Identity
	if (stack::empty()) {
		stack::push(glm::mat4(1.0f));
	}
}

void MatrixStack::identity() {
	stack::top() = glm::mat4(1.0f);
}

void MatrixStack::load(const glm::mat4& mat) {
	stack::top() = mat;
}

MatrixStack& MatrixStack::operator=(const glm::mat4& mat) {
	stack::top() = mat;
	return *this;
}

void MatrixStack::pre_multiply(const glm::mat4& mat) {
	stack::top() = mat * stack::top();
}

void MatrixStack::post_multiply(const glm::mat4& mat) {
	stack::top() = stack::top() * mat;
}

void MatrixStack::reset() {
	while(!stack::empty()) {
		stack::pop();
	}
	stack::push(glm::mat4(1.0f));
}

MatrixStack::operator const glm::mat4&() const {
	return stack::top();
}

MatrixStack::operator glm::mat4&() {
	return stack::top();
}


void MatrixStack::to_uniform(GLuint program, GLint location) const {
	glProgramUniformMatrix4fv(program, location, 1, false, value_ptr());
}

const GLfloat* MatrixStack::value_ptr() const {
	return glm::value_ptr(stack::top());
}

MatrixStack::Backup::~Backup() {
	_parent.pop();
}

MatrixStack::Backup::Backup(MatrixStack& parent)
	: _parent(parent) {
	_parent.push();
}
