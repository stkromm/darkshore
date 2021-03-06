#pragma once

#include <memory>

// Without gl defined before glew error
#include "graphics/renderer.h"
#include "scene/renderable.h"

#include "sprite_batch.h"
#include "platform/asset_manager.h"
#include "game/camera.h"

namespace ds {
	namespace scene
	{
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
	}
}