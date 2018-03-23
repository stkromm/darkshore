#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "json.h"

#include "scripting/script_manager.h"
#include "graphics/render_manager.h"
#include "platform/window_manager.h"
#include "platform/asset_manager.h"
#include "physics/physics.h"
#include "animation/animation_manager.h"

#include "core/game.h"
#include "gameplay/player.h"
#include "tilemap/level_loader.h"

int main(const int argc, char** argv)
{
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
	if (!physics::init())
	{
		return -1;
	}
	if (!AnimationManager::init())
	{
		return -1;
	}

	auto game = new Game();
	std::cout << "Load level" << std::endl;
	const std::string map_path = settings["start-level"];
	load_level(game, map_path);
	
	game->add_object<Player>();
	for (int i = 0; i < 10; ++i)
		game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);

	// Game Loop

	game->start();
	while (game->is_running)
	{
		platform::WindowManager::get_window().poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();

		int loops = 0;
		float escaped_time = 0;

		while (loops < game->MAX_FRAME_SKIP &&
			std::chrono::high_resolution_clock::now() > game->frame_fixed_end)
		{
			physics::tick(game->TICK_DELTA_MILLIS * 0.001f * 0.5f);
			game->simulate_step();
			physics::tick(game->TICK_DELTA_MILLIS * 0.001f * 0.5f);
			escaped_time += game->TICK_DELTA_MILLIS;
			loops++;
		}

		AnimationManager::update(escaped_time);
		graphics::SceneManager::get_scene()->render(game->get_tick_interpolation());
		platform::WindowManager::get_window().swap_buffers();
	}

	delete game;

	AnimationManager::shutdown();
	physics::shutdown();
	scripting::ScriptManager::shutdown();
	graphics::SceneManager::shutdown();
	graphics::RenderManager::shutdown();
	platform::WindowManager::shutdown();

	AssetManager::clean();
	return 0;
}
