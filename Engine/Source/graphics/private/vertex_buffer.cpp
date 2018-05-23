#include "graphics/vertex_buffer.h"
#include "graphics/graphics.h"
#include "core/logger/log.h"

ds::graphics::VertexBuffer::VertexBuffer(const void* data, const uint32_t size)
{
	LOG_INFO << "Creating VertexBuffer" << LOG_END;
	capacity = size;
	GLCall(glGenBuffers(1, &id));
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

ds::graphics::VertexBuffer::VertexBuffer(std::vector<float> data) : VertexBuffer(data.data(), data.size() * sizeof(float))
{
}

ds::graphics::VertexBuffer::~VertexBuffer()
{
	unbind();
	GLCall(glDeleteBuffers(1, &id));
}

template<class T>
void ds::graphics::VertexBuffer::update(std::vector<T> data)
{
	update(data.data(), sizeof(T) * data.size());
}

void ds::graphics::VertexBuffer::update(const void* data, const uint32_t size)
{
	bind();
	if (size > capacity)
	{
		capacity = size;
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW));
		LOG_INFO << "New vertex buffer capacity " << capacity << LOG_END;
	}
	else
	{
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}
}

void ds::graphics::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void ds::graphics::VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
