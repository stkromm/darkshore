#pragma once

#include "scene.h"

namespace graphics
{
	namespace SceneManager
	{
		Scene* get_scene();
		bool init();
		void shutdown();
	};
}
