#include "graphics/scene.h"
#include "graphics/render_manager.h"

graphics::Scene* scene = nullptr;

graphics::Scene* graphics::SceneManager::get_scene()
{
	return scene;
}

bool graphics::SceneManager::init()
{
	std::cout << "Created scene" << std::endl;
	scene = new Scene();
	return true;
}

void graphics::SceneManager::shutdown()
{
	delete scene;
}

void graphics::Scene::add_renderable(const std::shared_ptr<Renderable> renderable)
{
	renderables.push_back(renderable);
}

void graphics::Scene::render(const float interpolation)
{
	if (!get_camera()) return;

	RenderManager::get_scene_renderer()->prepare();
	RenderManager::get_sprite_renderer()->prepare(get_camera()->get_projection());

	for (const auto& renderable : renderables)
	{
		renderable->draw(interpolation);
	}

	RenderManager::get_sprite_renderer()->flush();

	//std::cout << "draw_calls# " << RenderManager::get_scene_renderer()->draw_calls << std::endl;
}
