#pragma once

#include <vector>
#include "core/types.h"

namespace ds {
	namespace graphics {

		enum VertexBufferElementType
		{
			UNSIGNED_INT,
			BYTE,
			FLOAT
		};

		struct VertexBufferElement
		{
			uint32_t count = 3;
			VertexBufferElementType type;
			bool normalized = false;
		};

		class VertexBufferLayout
		{
		private:
			uint32_t stride = 0;
			std::vector<VertexBufferElement> elements;
		public:
			VertexBufferLayout() = default;

			~VertexBufferLayout() = default;

			template <typename T>
			void push(uint32_t count, bool normalized = false)
			{
				static_assert(false);
			}

			uint32_t get_stride() const
			{
				return stride;
			}

			const std::vector<VertexBufferElement>& get_elements() const
			{
				return elements;
			}
		};
	};

	template <>
	inline void graphics::VertexBufferLayout::push<float>(const uint32_t count, bool normalized)
	{
		elements.push_back({ count, FLOAT, true });
		stride += sizeof(float) * count;
	}

	template <>
	inline void graphics::VertexBufferLayout::push<byte>(const uint32_t count, bool normalized)
	{
		elements.push_back({ count, BYTE, true });
		stride += sizeof(byte) * count;
	}

	template <>
	inline void graphics::VertexBufferLayout::push<uint32_t>(const uint32_t count, bool normalized)
	{
		elements.push_back({ count, UNSIGNED_INT, false });
		stride += sizeof(uint32_t) * count;
	}
}
