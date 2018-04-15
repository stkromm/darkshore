#pragma once

#include <memory>

#include "graphics/renderer.h"
#include "graphics/renderable.h"

#include "core/math/mat4x4.h"
#include "core/transform.h"
#include "platform/window_manager.h"
#include "sprite_batch.h"
#include "platform/asset_manager.h"

namespace graphics
{
	struct Camera
	{
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

		math::Mat4x4 get_projection() const
		{
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			const float aspect = float(screen.height) / screen.width;
			const float width = 1920;
			const float height = 1920 * aspect;
			const math::Mat4x4 world_to_local = transform->get_world_to_local();
			return world_to_local * math::Mat4x4(1).orthographic(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -1, 1);
		}
	};


	class Scene
	{
	public:
		std::vector<std::shared_ptr<Renderable>> renderables;
		std::shared_ptr<Camera> camera;

		Scene()
		{
			camera = std::make_shared<Camera>();
		}

		~Scene()
		{
			std::cout << "Delete scene" << std::endl;
		}

		void set_camera(const std::shared_ptr<Camera> camera)
		{
			this->camera = camera;
		}

		std::shared_ptr<Camera> get_camera() const
		{
			return camera;
		}

		void add_renderable(std::shared_ptr<Renderable> renderable);

		void render(float interpolation);
	};

	namespace SceneManager
	{
		Scene* get_scene();
		bool init();
		void shutdown();
	};
}
