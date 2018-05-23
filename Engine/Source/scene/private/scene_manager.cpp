#include "scene/scene_manager.h"
#include "core/logger/log.h"
#include "scene/scene.h"

graphics::Scene* scene = nullptr;

graphics::Scene* graphics::SceneManager::get_scene()
{
	return scene;
}

bool graphics::SceneManager::init()
{
	scene = new Scene();
	LOG_INFO << "Created scene" << LOG_END;
	return true;
}

void graphics::SceneManager::shutdown()
{
	delete scene;
}
