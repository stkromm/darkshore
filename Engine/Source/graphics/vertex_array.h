#pragma once

#include "graphics/vertex_buffer.h"
#include "graphics/vertex_buffer_layout.h"

namespace ds {
	namespace graphics {
		class IndexBuffer;

		class VertexArray
		{
		private:
			mutable int attribute_count = 0;
			uint32_t id = 0;
		public:
			VertexArray();
			~VertexArray();

			void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;
			void set_attribute_divisor(uint32 attribute_id, uint32 divisor) const;
			void bind() const;
			void draw_instanced(const IndexBuffer& index_buffer, uint32 instance_count) const;
			void draw(const IndexBuffer& index_buffer) const;
			void unbind() const;

			bool operator==(const VertexArray& vertex_array) const
			{
				return vertex_array.id == id;
			}
		};
	}
}