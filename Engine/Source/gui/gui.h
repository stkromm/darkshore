#pragma once

#include <vector>

#include "core/types.h"
#include "core/math/vec2.h"
#include "core/logger/log.h"

namespace ds {
	namespace gui {
		class GuiElement {
		protected:
			ds::Vec2<int32> position;

			bool dirty = true;
		public:

			void mark_rendered()
			{
				dirty = false;
			};
			bool needs_rerender()
			{
				return dirty;
			};
		};
		class Gui {
			std::vector<std::shared_ptr<GuiElement>> elements;
		public:
			Gui() {

			}

			void add_element(std::shared_ptr<GuiElement> element) {
				elements.push_back(element);
			}
			void remove_element(std::shared_ptr<GuiElement> element) {
				// elements.erase(elements.find)
			}
			void render(float interpolation) {
				for (const auto& element : elements)
				{
					if (element->needs_rerender()) {
						element->mark_rendered();
						LOG_INFO << "Calculated rerender" << LOG_END;
					}
				}
			}
		};
	}
}