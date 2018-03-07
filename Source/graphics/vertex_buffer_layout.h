#pragma once

#include <vector>

#include "core/types.h"

namespace graphics
{
	enum VertexBufferElementType
	{
		UNSIGNED_INT, BYTE, FLOAT
	};

	struct VertexBufferElement {
		uint32_t count = 3;
		VertexBufferElementType type;
		bool normalized = false;
	};

	class VertexBufferLayout {
	private:
		uint32_t stride = 0;
		std::vector<VertexBufferElement> elements;
	public:
		VertexBufferLayout() {}
		~VertexBufferLayout() {}

		template<typename T>
		void push(uint32_t count, bool normalized = false)
		{
			static_assert(false);
		}

		template<>
		inline void push<float>(uint32_t count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::FLOAT, true });
			stride += sizeof(float) * count;
		}

		template<>
		inline void push<byte>(uint32_t count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::BYTE, true });
			stride += sizeof(byte) * count;
		}

		template<>
		inline void push<uint32_t>(uint32_t count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::UNSIGNED_INT, false });
			stride += sizeof(uint32_t) * count;
		}

		inline uint32_t get_stride() const {
			return stride;
		}

		inline const std::vector<VertexBufferElement>& get_elements() const {
			return elements;
		}
	};
};
