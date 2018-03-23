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

	public:
		IndexBuffer(const uint32_t* data, uint32_t count);

		explicit IndexBuffer(std::vector<uint32_t> data) : IndexBuffer(data.data(), data.size())
		{
		};
		~IndexBuffer();

		uint32_t get_count() const
		{
			return count;
		}

		void bind() const;
		void unbind() const;
	};
}
