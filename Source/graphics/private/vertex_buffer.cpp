#include "graphics\vertex_buffer.h"

graphics::VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

graphics::VertexBuffer::VertexBuffer(std::vector<float> data) : VertexBuffer(data.data(), data.size() * sizeof(float))
{
}

graphics::VertexBuffer::~VertexBuffer()
{
	unbind();
	GLCall(glDeleteBuffers(1, &id));
}

void graphics::VertexBuffer::update(const void* data, uint32_t size)
{
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void graphics::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void graphics::VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}