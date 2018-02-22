#pragma once

#include "graphics/graphics.h"
#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"

namespace graphics {
	class Renderer
	{
	public:
		void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) {

			shader.bind();

			vertex_array.bind();
			index_buffer.bind();

			GLCall(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));
		}

		void prepare() {
			GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
		}
	};
}

