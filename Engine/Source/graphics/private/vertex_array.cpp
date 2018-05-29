#include "graphics/vertex_array.h"
#include "graphics/graphics.h"
#include "core/logger/log.h"
#include "graphics/index_buffer.h"

static uint32_t to_gl_element_type(const ds::graphics::VertexBufferElementType type)
{
	switch (type)
	{
	case ds::graphics::VertexBufferElementType::FLOAT:
		return GL_FLOAT;
	case ds::graphics::VertexBufferElementType::BYTE:
		return GL_UNSIGNED_BYTE;
	case ds::graphics::VertexBufferElementType::UNSIGNED_INT:
		return GL_UNSIGNED_INT;
	}
	ASSERT(false);
	return 0;
}

static uint32_t get_size_of_vertex_buffer_type(const ds::graphics::VertexBufferElementType type)
{
	switch (type)
	{
	case ds::graphics::VertexBufferElementType::FLOAT:
		return 4;
	case ds::graphics::VertexBufferElementType::BYTE:
		return 1;
	case ds::graphics::VertexBufferElementType::UNSIGNED_INT:
		return 4;
	}
	ASSERT(false);
	return 0;
}

ds::graphics::VertexArray::VertexArray()
{
	LOG_INFO << "Creating VertexArray" << LOG_END;
	GLCall(glGenVertexArrays(1, &id));
	bind();
};

ds::graphics::VertexArray::~VertexArray()
{
	unbind();
	GLCall(glDeleteVertexArrays(1, &id));
};

void ds::graphics::VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
	bind();
	vb.bind();
	const auto& elements = layout.get_elements();
	uint32_t offset = 0;
	for (size_t i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i + attribute_count));
		GLCall(glVertexAttribPointer(i + attribute_count, element.count, to_gl_element_type(element.type), element.normalized ? GL_TRUE :
			GL_FALSE, layout.get_stride(), reinterpret_cast<const void*>(offset)));

		offset += element.count * get_size_of_vertex_buffer_type(element.type);
	}
	attribute_count += elements.size(); 
}

void ds::graphics::VertexArray::set_attribute_divisor(const uint32 attribute_id, const uint32 divisor) const
{
	ASSERT(attribute_id <= uint32(attribute_count));
	GLCall(glVertexAttribDivisor(attribute_id, divisor));
}

void ds::graphics::VertexArray::bind() const
{
	GLCall(glBindVertexArray(id));
}

void ds::graphics::VertexArray::draw_instanced(const IndexBuffer& index_buffer, const uint32 instance_count) const
{
	bind();
	index_buffer.bind();
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr, instance_count));
}

void ds::graphics::VertexArray::draw(const IndexBuffer& index_buffer) const
{
	bind();
	index_buffer.bind();
	GLCall(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));
}

void ds::graphics::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
