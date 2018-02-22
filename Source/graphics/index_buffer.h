#pragma once

#include <vector>

#include "graphics/graphics.h"

namespace graphics {
	class IndexBuffer {
	private:
		size_t id;
		size_t count;

	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		IndexBuffer(std::vector<unsigned int> data) : IndexBuffer(data.data(), data.size()) {};
		~IndexBuffer();

		unsigned int get_count() const {
			return count;
		}

		void bind() const;
		void unbind() const;
	};
}