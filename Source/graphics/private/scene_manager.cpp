#include "graphics/scene_manager.h"
#include "core/logger/log.h"

graphics::Scene* scene = nullptr;

graphics::Scene* graphics::SceneManager::get_scene()
{
	return scene;
}

bool graphics::SceneManager::init()
{
	LOG_INFO << "Created scene";
	scene = new Scene();
	return true;
}

void graphics::SceneManager::shutdown()
{
	delete scene;
}
