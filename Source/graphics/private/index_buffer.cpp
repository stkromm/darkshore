#include "graphics/index_buffer.h"

graphics::IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count) : count(count) {
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

graphics::IndexBuffer::~IndexBuffer() {
	unbind();
	GLCall(glDeleteBuffers(1, &id));
}

void graphics::IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void graphics::IndexBuffer::unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}