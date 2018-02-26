#pragma once
#include <vector>

#include "graphics/graphics.h"

namespace graphics {
	
	enum VertexBufferElementType {
		UNSIGNED_INT, UNSIGNED_BYTE, FLOAT
	};

	struct VertexBufferElement {
		unsigned int count = 3;
		VertexBufferElementType type;
		bool normalized = false;
	};

	class VertexBufferLayout {
	private:
		unsigned int stride = 0;
		std::vector<VertexBufferElement> elements;
	public:
		VertexBufferLayout() {}
		~VertexBufferLayout() {}

		template<typename T>
		void push(unsigned int count, bool normalized = false)
		{
			static_assert(false);
		}

		template<>
		void push<float>(unsigned int count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::FLOAT, true });
			stride += sizeof(float) * count;
		}

		template<>
		void push<unsigned char>(unsigned int count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::UNSIGNED_BYTE, true });
			stride += sizeof(unsigned char) * count;
		}

		template<>
		void push<unsigned int>(unsigned int count, bool normalized)
		{
			elements.push_back({ count, VertexBufferElementType::UNSIGNED_INT, false });
			stride += sizeof(unsigned int) * count;
		}

		inline unsigned int get_stride() const {
			return stride;
		}

		inline const std::vector<VertexBufferElement>& get_elements() const {
			return elements;
		}
	};

	class VertexBuffer {
	private:
		size_t id;
	public:
		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer(std::vector<float> data);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
	};
}