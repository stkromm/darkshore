#include "scene.h"

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