#include <string>
#include "gui/gui.h"

namespace ds {
	namespace gui {
		class Text : GuiElement {
			std::string text;
		public:
			Text(std::string text);
			void set_text(std::string text);
			std::string get_render_text();
		};
	}
}