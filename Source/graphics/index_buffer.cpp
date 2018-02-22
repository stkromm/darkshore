#include "graphics/index_buffer.h"

graphics::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : count(count) {
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

graphics::IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &id));
}

void graphics::IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void graphics::IndexBuffer::unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}