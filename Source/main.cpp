#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "json.h"

#include "scripting/script.h"
#include "graphics/render_manager.h"
#include "platform/window.h"
#include "platform/asset.h"

#include "game.h"

int main(const int argc, char** argv) {
	std::cout << "Vine Engine started" << std::endl;

	std::ifstream config_file("config.json");
	json settings;
	if (config_file.is_open())
		config_file >> settings;
	else
		settings = {};
	if (!AssetManager::init())
	{
		return -1;
	}
	if (!platform::WindowManager::init())
	{
		return -1;
	}
	if (!graphics::RenderManager::init())
	{
		return -1;
	}
	if (!graphics::SceneManager::init())
	{
		return -1;
	}
	if (!scripting::ScriptManager::init())
	{
		return -1;
	}


	Game* game = new Game();
	std::cout << "Load level" << std::endl;
	std::string map_path = settings["start-level"];
	game->load_level(map_path);

	// Game Loop
	int loops = 0;
	const auto tick_delta_nanos = std::chrono::nanoseconds((int)(game->TICK_DELTA_MILLIS * 1000000.0f));

	game->start();
	while (game->is_running) {
		platform::WindowManager::get_window().poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();

		loops = 0;

		while (loops < game->MAX_FRAME_SKIP &&
			std::chrono::high_resolution_clock::now() > game->frame_fixed_end)
		{
			game->simulate_step();
			loops++;
		}

		graphics::SceneManager::get_scene()->render(game->get_tick_interpolation());

		platform::WindowManager::get_window().swap_buffers();
	}

	delete game;

	scripting::ScriptManager::shutdown();
	graphics::SceneManager::shutdown();
	graphics::RenderManager::shutdown();
	platform::WindowManager::shutdown();

	AssetManager::clean();
	return 0;
}