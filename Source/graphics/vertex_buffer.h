#pragma once
#include <vector>

#include "graphics/graphics.h"

namespace graphics
{
	class VertexBuffer
	{
	private:
		uint32_t capacity = 0;
		uint32_t id = 0;
	public:
		VertexBuffer(const void* data, uint32_t size);
		explicit VertexBuffer(std::vector<float> data);
		~VertexBuffer();

		void update(const void* data, uint32_t size);
		template<class T> void update(std::vector<T> data);

		void bind() const;
		void unbind() const;
	};
}
