#pragma once

#include <vector>

#include "graphics\vertex_buffer.h"

namespace graphics
{
	class VertexArray
	{
	private:
		unsigned int id;
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