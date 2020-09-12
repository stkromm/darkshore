#pragma once

#include <string>
#include "gui/gui.h"
#include "gui/text.h"
#include "scene/standalone_sprite.h"

namespace ds {
	namespace gui {

		class Button : GuiElement {
			std::string text;
			std::shared_ptr<gui::Text> button_text;
			std::shared_ptr<scene::StandaloneSprite> button_box;
		public:
			Button(std::string text) {
				button_text = std::make_shared<gui::Text>(text);

				gui::Gui::add_element(button_text);
				button_text->set_position(this->position.x, this->position.y);
			}
			void set_position(int32 x, int32 y) override {
				position.x = x;
				position.y = y;
				button_text->set_position(this->position.x, this->position.y);
			}
			virtual bool needs_rerender() override {
				return button_text->needs_rerender();
			}
			void set_text(std::string text);
			std::string get_render_text() const;
			std::vector<GlyphVertex> get_vertex_data() const;
			Mat4x4 get_transformation() const;
			std::shared_ptr<graphics::Texture> get_texture() const;
		};
	}
}