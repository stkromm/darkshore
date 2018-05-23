#include "graphics/renderer.h"

#include "graphics/graphics.h"

namespace ds {
	namespace graphics {
		SceneRenderer::SceneRenderer()
		{
			//	framebuffer = std::make_shared<Framebuffer>(1024,720);
		}

		void SceneRenderer::draw(const ds::graphics::VertexArray& vertex_array, const ds::graphics::IndexBuffer& index_buffer, const ds::graphics::Shader& shader) const
		{
			shader.bind();

			vertex_array.bind();
			index_buffer.bind();

			GLCall(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));
			draw_calls++;

		}

		void SceneRenderer::prepare() const
		{
			//framebuffer->bind();

			draw_calls = 0;
			GLCall(glClearColor(.0f, .0f, .0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
		}
	}
}