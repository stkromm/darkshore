#include "scene/render_manager.h"

#include "graphics/graphics.h"
#include "platform/asset_manager.h"
#include "core/logger/log.h"
#include "res.h"
#include <memory>
#include "scene/shader_asset.h"

std::shared_ptr<ds::graphics::SceneRenderer> scene_renderer;
std::shared_ptr<graphics::DynamicSpriteBatch> sprite_batch;
std::shared_ptr<ShaderAsset> shader;

std::shared_ptr<graphics::DynamicSpriteBatch> graphics::RenderManager::get_sprite_renderer()
{
	return sprite_batch;
}

std::shared_ptr<ds::graphics::SceneRenderer> graphics::RenderManager::get_scene_renderer()
{
	return scene_renderer;
}

bool graphics::RenderManager::init()
{
	if (!ds::graphics::init())
	{
		return false;
	}

	scene_renderer = std::make_shared<ds::graphics::SceneRenderer>();
	shader = AssetManager::load_asset<ShaderAsset>("batch.shader");
	sprite_batch = std::make_shared<DynamicSpriteBatch>(scene_renderer, shader->shader);

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
