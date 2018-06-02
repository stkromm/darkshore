#pragma once

#include "scene.h"

namespace ds {
	namespace scene
	{
		namespace SceneManager
		{
			Scene* get_scene();
			bool init();
			void shutdown();
		};
	}
}