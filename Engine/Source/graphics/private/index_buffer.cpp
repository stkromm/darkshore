#include "graphics/index_buffer.h"

#include "graphics/graphics.h"

ds::graphics::IndexBuffer::IndexBuffer(const uint32_t* data, const uint32_t count) : count(count)
{
	capacity = count;
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

void ds::graphics::IndexBuffer::update(const std::vector<unsigned>& indices)
{
	bind();
	if (indices.size() > capacity)
	{
		capacity = indices.size();
		count = indices.size();
		LOG_INFO << "Count is " << count << LOG_END;
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STREAM_DRAW));
	}
	else
	{
		count = indices.size();
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(uint32_t), indices.data()));
	}
}

ds::graphics::IndexBuffer::~IndexBuffer()
{
	unbind();
	GLCall(glDeleteBuffers(1, &id));
}

static uint32 last_bound_buffer = 0;

void ds::graphics::IndexBuffer::set_count(const uint32 count)
{
	this->count = count;
}

void ds::graphics::IndexBuffer::bind() const
{
	if (last_bound_buffer != id)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		last_bound_buffer = id;
	}
}

void ds::graphics::IndexBuffer::unbind() const
{
	if(last_bound_buffer != 0)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		last_bound_buffer = 0;
	}
}
