#pragma once

#include "graphics/renderer.h"
#include "graphics/renderable.h"

#include "platform/window.h"

namespace graphics {

	class Quad : public Renderable {
		std::vector<float> vertices_array =
		{
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.5f,  0.5f, 0.f,
			-0.5f,  0.5f, 0.f
		};

		unsigned int indices[6] = {
			0,1,2,2,3,0
		};

		const Shader* shader;
		const VertexBuffer* vertex_buffer;
		const VertexArray* vertex_array;
		const IndexBuffer* index_buffer;
	public:
		Quad()
		{
			vertex_array = new VertexArray();
			vertex_buffer = new VertexBuffer(vertices_array);
			index_buffer = new IndexBuffer(indices, 6);

			VertexBufferLayout vb_layout;
			vb_layout.push<float>(3);
			vertex_array->add_buffer(*vertex_buffer, vb_layout);
			shader = new Shader("basic.shader");
		}

		~Quad()
		{
			delete shader;
			delete vertex_buffer;
			delete vertex_array;
			delete index_buffer;

		}

		void draw(Renderer& renderer) const override
		{
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};

	struct Camera {
		math::Mat4x4 get_projection() const {
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			return math::Mat4x4(1).orthographic(- screen.width / 2.f, screen.width / 2.f, -screen.height / 2.f, screen.height / 2.f, -1, 1);
		}
	};
	class Scene
	{
	public:
		std::vector<Renderable*> renderables;
		Renderer* renderer;
		Camera camera;
		Scene()
		{
			renderer = new Renderer();
		}

		~Scene()
		{
			delete renderer;
		}

		const Camera& get_camera() const {
			return camera;
		}

		void add_renderable(Renderable* renderable) {
			renderable->set_scene(this);
			renderables.push_back(renderable);
		}

		void render(const float interpolation)
		{
			std::cout << "Interpolation " << interpolation << std::endl;
			renderer->prepare();
			for (const auto renderable : renderables)
			{
				renderable->draw(*renderer);
			}
		}
	};
}