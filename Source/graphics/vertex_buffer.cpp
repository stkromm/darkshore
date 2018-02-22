#include "graphics\vertex_buffer.h"

graphics::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
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
	GLCall(glDeleteBuffers(1, &id));
}

void graphics::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}