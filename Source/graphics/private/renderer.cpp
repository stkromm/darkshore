#include "graphics/renderer.h"

namespace graphics {

	void Renderer::draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) {

		shader.bind();

		vertex_array.bind();
		index_buffer.bind();

		GLCall(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::prepare() {
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
	}
};