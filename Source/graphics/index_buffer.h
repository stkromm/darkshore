#pragma once

#include <vector>

#include "graphics/graphics.h"

namespace graphics
{
	class IndexBuffer
	{
	private:
		uint32_t id = 0;
		uint32_t count;
		uint32_t capacity;

	public:
		IndexBuffer(const uint32_t* data, uint32_t count);

		explicit IndexBuffer(std::vector<uint32_t> data) : IndexBuffer(data.data(), data.size())
		{
		}

		void update(const std::vector<unsigned>& indices);

		~IndexBuffer();

		uint32_t get_count() const
		{
			return count;
		}

		void bind() const;
		void unbind() const;
	};
}
