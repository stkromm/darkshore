#pragma once

#include <memory>

#include "graphics/renderer.h"
#include "graphics/renderable.h"

#include "platform/window.h"

namespace graphics {

	struct Camera {
		std::shared_ptr<Transform> transform;
		float zoom = 1.25f;

		Camera()
		{
			transform = std::make_shared<Transform>();
			transform->scale(zoom);
		}

		~Camera()
		{
			std::cout << "Delete camera" << std::endl;
		}

		math::Mat4x4 get_projection() const {
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			float aspect = (float)screen.height / (float)screen.width;
			float width = 1920;
			float height = 1920 * aspect;
			return transform->get_world_to_local() * math::Mat4x4(1).orthographic(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -1, 1);
		}
	};


	class Scene
	{
	public:
		std::vector<std::shared_ptr<Renderable>> renderables;
		std::shared_ptr<Renderer> renderer;
		std::shared_ptr<Camera> camera;

		Scene()
		{
			renderer = std::make_shared<Renderer>();
			camera = std::make_shared<Camera>();
		}

		~Scene()
		{
			std::cout << "Delete scene" << std::endl;
		}

		void set_camera(std::shared_ptr<Camera> camera)
		{
			this->camera = camera;
		}

		const std::shared_ptr<Camera> get_camera() const {
			return camera;
		}

		void add_renderable(std::shared_ptr<Renderable> renderable) {
			renderables.push_back(renderable);
		}

		void render(const float interpolation)
		{
			if (!get_camera()) return;
			//std::cout << "Interpolation " << interpolation << std::endl;
			renderer->prepare();
			//std::cout << "Draw #Renderables:" << renderables.size() << std::endl;
			for (const auto renderable : renderables)
			{
				renderable->draw(interpolation, *renderer);
			}
		}
	};
	namespace SceneManager
	{
		Scene* get_scene();
		bool init();
		void shutdown();
	};
}