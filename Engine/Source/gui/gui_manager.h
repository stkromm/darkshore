#pragma once

#include "gui.h"

namespace ds {
	namespace gui
	{
		namespace GuiManager
		{
			Gui* get_gui();
			bool init();
			void shutdown();
		};
	}
}