#pragma once
#include <vector>

#include "graphics/graphics.h"

namespace graphics {

	class VertexBuffer {
	private:
		uint32_t id;
	public:
		VertexBuffer(const void* data, uint32_t size);
		VertexBuffer(std::vector<float> data);
		~VertexBuffer();

		void update(const void* data, uint32_t size);

		void bind() const;
		void unbind() const;
	};
}