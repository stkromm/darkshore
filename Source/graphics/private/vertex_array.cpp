#include "graphics/vertex_array.h"

static uint32_t to_gl_element_type(const graphics::VertexBufferElementType type)
{
	switch (type)
	{
	case graphics::VertexBufferElementType::FLOAT:
		return GL_FLOAT;
	case graphics::VertexBufferElementType::BYTE:
		return GL_UNSIGNED_BYTE;
	case graphics::VertexBufferElementType::UNSIGNED_INT:
		return GL_UNSIGNED_INT;
	}
	ASSERT(false);
	return 0;
}

static uint32_t get_size_of_vertex_buffer_type(const graphics::VertexBufferElementType type)
{
	switch (type)
	{
	case graphics::VertexBufferElementType::FLOAT:
		return 4;
	case graphics::VertexBufferElementType::BYTE:
		return 1;
	case graphics::VertexBufferElementType::UNSIGNED_INT:
		return 4;
	}
	ASSERT(false);
	return 0;
}

graphics::VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &id));
	bind();
};

graphics::VertexArray::~VertexArray()
{
	unbind();
	GLCall(glDeleteVertexArrays(1, &id));
};

void graphics::VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
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

void graphics::VertexArray::bind() const
{
	GLCall(glBindVertexArray(id));
}

void graphics::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
