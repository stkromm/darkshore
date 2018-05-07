#include "graphics/index_buffer.h"

graphics::IndexBuffer::IndexBuffer(const uint32_t* data, const uint32_t count) : count(count)
{
	capacity = count;
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

void graphics::IndexBuffer::update(const std::vector<unsigned>& indices)
{
	bind();
	if(indices.size() > capacity)
	{
		capacity = indices.size();
		count = indices.size();
		std::cout << "Count is " << count << std::endl;
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW));
	}
	else
	{
		count = indices.size();
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(uint32_t), indices.data()));
	}
}

graphics::IndexBuffer::~IndexBuffer()
{
	unbind();
	GLCall(glDeleteBuffers(1, &id));
}

void graphics::IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void graphics::IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
