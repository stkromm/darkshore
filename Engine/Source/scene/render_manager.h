#pragma once

#include "graphics/renderer.h"
#include "sprite_batch.h"

namespace ds {
	namespace scene
	{
		namespace RenderManager
		{
			std::shared_ptr<DynamicSpriteBatch> get_sprite_renderer();
			std::shared_ptr<graphics::SceneRenderer> get_scene_renderer();

			bool init();

			void prepare();

			inline void shutdown()
			{
			}

			void flush();
		};
	};
}