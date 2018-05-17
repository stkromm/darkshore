#include "graphics/render_manager.h"

#include "graphics/graphics.h"
#include "core/platform/asset_manager.h"
#include "core/logger/log.h"
#include "res.h"

std::shared_ptr<graphics::SceneRenderer> scene_renderer;
std::shared_ptr<graphics::DynamicSpriteBatch> sprite_batch;

std::shared_ptr<graphics::DynamicSpriteBatch> graphics::RenderManager::get_sprite_renderer()
{
	return sprite_batch;
}

std::shared_ptr<graphics::SceneRenderer> graphics::RenderManager::get_scene_renderer()
{
	return scene_renderer;
}

bool graphics::RenderManager::init()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW init failed" << std::endl;
		return false;
	}
	LOG_INFO << glGetString(GL_VERSION) << LOG_END;
	LOG_INFO << glGetString(GL_VENDOR) << LOG_END;
	LOG_INFO << glGetString(GL_RENDERER) << LOG_END;
	LOG_INFO << glGetString(GL_SHADING_LANGUAGE_VERSION) << LOG_END;

	scene_renderer = std::make_shared<SceneRenderer>();
	sprite_batch = std::make_shared<DynamicSpriteBatch>(scene_renderer, AssetManager::load_asset<Shader>("batch.shader"));
	return true;
}

void graphics::RenderManager::prepare()
{
	scene_renderer->prepare();
}

void graphics::RenderManager::flush()
{
	sprite_batch->flush();
}
