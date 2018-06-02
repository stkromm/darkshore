#include "scene/scene_manager.h"
#include "core/logger/log.h"
#include "scene/scene.h"

using namespace ds::scene;

Scene* s_scene = nullptr;

Scene* SceneManager::get_scene()
{
	return s_scene;
}

bool SceneManager::init()
{
	s_scene = new Scene();
	LOG_INFO << "Created scene" << LOG_END;
	return true;
}

void SceneManager::shutdown()
{
	delete s_scene;
}
