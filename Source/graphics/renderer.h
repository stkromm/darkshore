#pragma once

#include <iostream>

#include "core/math/vec2.h"
#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"

namespace graphics
{
	class SceneRenderer
	{
	public:
		mutable uint32_t draw_calls;

		~SceneRenderer()
		{
			std::cout << "Delete renderer" << std::endl;
		}

		void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;
		void prepare() const;
	};

	class GUIRenderer
	{
		void draw_rectangle(math::Vec2 position, math::Vec2 size);
		void fill_rectangle(math::Vec2 position, math::Vec2 size, uint_fast32_t color);
		void draw_string(const std::string& text, math::Vec2 position);
	};
};
