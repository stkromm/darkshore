#pragma once

#include <string>

#include "game/game.h"
#include "audio/music.h"
#include "gui/text.h"
#include "gui/gui_manager.h"
#include "platform/window.h"

#include "gameplay/player.h"
#include "tilemap/tilemap.h"

namespace ds
{
	namespace game
	{
		
		inline void load_level(Game* game, const std::string& name)
		{

			// ds::audio::BackgroundMusic::play("music.wav");
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			const float width = screen.width;
			const float height = screen.height;

			auto exit_button_text = std::make_shared<gui::Text>("Exit");
			auto exit_button = std::reinterpret_pointer_cast<gui::GuiElement>(exit_button_text);
			exit_button->set_position(width / 2 - 50, height / 2 - 20);
			auto start_button = std::reinterpret_pointer_cast<gui::GuiElement>(std::make_shared<gui::Text>("New Game"));
			start_button->set_position(width / 2 - 50, height / 2 - 50);
			gui::GuiManager::get_gui()->add_element(exit_button);
			gui::GuiManager::get_gui()->add_element(start_button);

			game->add_object<Player>();

			for (int i = 0; i < 1; ++i)
				game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);
			scene::SceneManager::get_scene()->add_renderable(std::make_shared<tilemap::TileMap>("map.tmx"));
			platform::WindowManager::get_window().add_cursor_position_callback([exit_button_text, width, height](double x, double y) {
				if (x > (width / 2 - 50.0f) / width && x < (width / 2 + 50.0f) / width && y > (height / 2 - 40.0f) / height && y < (height / 2 + 10.0f) / height) {
					exit_button_text->set_text("Start new Game");
				}
				else {
					exit_button_text->set_text("Hover me");
				}
			});
		}

	}
}