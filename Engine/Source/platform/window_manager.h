#pragma once

#include "platform/window.h"

namespace ds {
	namespace platform {
		namespace WindowManager
		{
			bool init();
			void shutdown();
			Window& get_window();
		};
	};
}