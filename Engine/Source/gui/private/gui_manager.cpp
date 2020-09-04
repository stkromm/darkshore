#include "gui/gui_manager.h"

namespace ds {
	namespace gui
	{
		namespace GuiManager
		{
			Gui* gui;

			Gui* get_gui() {
				return gui;
			}
			bool init() {
				gui = new Gui();
				return true;
			}
			void shutdown() {
				delete gui;
			}
		};
	}
}