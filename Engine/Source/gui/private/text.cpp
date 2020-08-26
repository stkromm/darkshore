#include "gui/text.h"

namespace ds {
	namespace gui {
		Text::Text(std::string text)
		{
			this->text = text;
			this->dirty = true;
		}
		void Text::set_text(std::string text)
		{
			this->text = text;
			this->dirty = true;
		}
		std::string Text::get_render_text()
		{
			return this->text;
		}
	};
};