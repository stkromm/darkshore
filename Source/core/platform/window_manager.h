#pragma once

#include "core/platform/window.h"

namespace platform
{
	namespace WindowManager
	{
		bool init();
		void shutdown();
		Window& get_window();
	};
};
