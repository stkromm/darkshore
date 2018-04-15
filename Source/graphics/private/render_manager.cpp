#include "graphics/render_manager.h"

#include "graphics/graphics.h"
#include "platform/asset_manager.h"

std::shared_ptr<graphics::GUIRenderer> gui_renderer;
std::shared_ptr<graphics::SceneRenderer> scene_renderer;
std::shared_ptr<graphics::DynamicSpriteBatch> sprite_batch;

std::shared_ptr<graphics::GUIRenderer> graphics::RenderManager::get_gui_renderer()
{
	return gui_renderer;
}

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

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	gui_renderer = std::make_shared<GUIRenderer>();
	scene_renderer = std::make_shared<SceneRenderer>();
	sprite_batch = std::make_shared<DynamicSpriteBatch>(scene_renderer, AssetManager::load_asset<Shader>("basic.shader"));
	return true;
}
