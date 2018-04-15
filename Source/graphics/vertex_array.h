#pragma once

#include "graphics/vertex_buffer.h"
#include "graphics/vertex_buffer_layout.h"

namespace graphics
{
	class VertexArray
	{
	private:
		mutable int attribute_count = 0;
		uint32_t id = 0;
	public:
		VertexArray();
		~VertexArray();

		void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

		void bind() const;
		void unbind() const;

		bool operator==(const VertexArray& vertex_array) const
		{
			return vertex_array.id == id;
		}
	};
}
