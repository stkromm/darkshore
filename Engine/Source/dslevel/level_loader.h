#pragma once

#include <string>

#include "game/game.h"
#include "audio/music.h"
#include "gui/text.h"
#include "gui/gui_manager.h"

#include "gameplay/player.h"

namespace ds
{
	namespace game
	{

		inline void load_level(Game* game, const std::string& name)
		{
			game->add_object<Player>();

			for (int i = 0; i < 50; ++i)
				game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);

			ds::audio::BackgroundMusic::play("music.wav");

			gui::GuiManager::get_gui()->add_element(std::reinterpret_pointer_cast<gui::GuiElement>(std::make_shared<gui::Text>("Hello World")));
		}

	}
}