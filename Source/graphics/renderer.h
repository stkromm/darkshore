#pragma once

#include <iostream>

#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"

namespace graphics
{
	class Renderer
	{
	public:
		~Renderer()
		{
			std::cout << "Delete renderer" << std::endl;
		}

		void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;
		void prepare() const;
	};
};
