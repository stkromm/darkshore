#pragma once

#include "graphics/renderer.h"
#include "sprite_batch.h"

namespace graphics
{
	namespace RenderManager
	{
		std::shared_ptr<GUIRenderer> get_gui_renderer();
		std::shared_ptr<DynamicSpriteBatch> get_sprite_renderer();
		std::shared_ptr<SceneRenderer> get_scene_renderer();

		bool init();

		inline void shutdown()
		{
		}
	};
};
