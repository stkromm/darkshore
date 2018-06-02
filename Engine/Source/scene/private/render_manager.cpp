#include "scene/render_manager.h"

#include "graphics/graphics.h"
#include "platform/asset_manager.h"
#include "core/logger/log.h"
#include "res.h"
#include <memory>
#include "scene/shader_asset.h"

using namespace ds::scene;
std::shared_ptr<ds::graphics::SceneRenderer> scene_renderer;
std::shared_ptr<DynamicSpriteBatch> sprite_batch;

std::shared_ptr<DynamicSpriteBatch> RenderManager::get_sprite_renderer()
{
	return sprite_batch;
}

std::shared_ptr<ds::graphics::SceneRenderer> RenderManager::get_scene_renderer()
{
	return scene_renderer;
}

bool RenderManager::init()
{
	if (!graphics::init())
	{
		return false;
	}

	scene_renderer = std::make_shared<graphics::SceneRenderer>();
	sprite_batch = std::make_shared<DynamicSpriteBatch>(scene_renderer);

	return true;
}

void RenderManager::prepare()
{
	scene_renderer->prepare();
}

void RenderManager::flush()
{
	sprite_batch->flush();
}
