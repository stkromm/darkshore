#include "graphics/renderer.h"

namespace graphics
{

	void SceneRenderer::draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const
	{
		shader.bind();

		vertex_array.bind();
		index_buffer.bind();

		GLCall(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));
		draw_calls++;
	}

	void SceneRenderer::prepare() const
	{
		draw_calls = 0;
		GLCall(glClearColor(.0f, .0f, .0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
	}
};
