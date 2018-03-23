#include "graphics/scene.h"

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
	//std::cout << "Interpolation " << interpolation << std::endl;
	renderer->prepare();
	//std::cout << "Draw #Renderables:" << renderables.size() << std::endl;
	for (const auto& renderable : renderables)
	{
		renderable->draw(interpolation, *renderer);
	}
}
