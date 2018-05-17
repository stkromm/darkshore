#include "graphics/vertex_buffer.h"
#include "core/logger/log.h"

graphics::VertexBuffer::VertexBuffer(const void* data, const uint32_t size)
{
	LOG_INFO << "Creating VertexBuffer" << LOG_END;
	capacity = size;
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

template<class T>
void graphics::VertexBuffer::update(std::vector<T> data)
{
	update(data.data(), sizeof(T) * data.size());
}

void graphics::VertexBuffer::update(const void* data, const uint32_t size) 
{
	bind();
	if (size > capacity)
	{
		capacity = size;
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		LOG_INFO << "New vertex buffer capacity " << capacity << LOG_END;
	}
	else
	{
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}
}

void graphics::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void graphics::VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
