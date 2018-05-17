#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "core/json/json.h"

#include "graphics/render_manager.h"
#include "core/platform/window_manager.h"
#include "scripting/script_manager.h"
#include "core/platform/asset_manager.h"
#include "physics/physics.h"
#include "animation/animation_manager.h"

#include "core/game.h"
#include "dslevel/level_loader.h"
#include "graphics/scene_manager.h"
#include "core/logger/log.h"
#include "core/time/time.h"


int main(const int argc, char** argv)
{
	LOG_INFO << "Vine Engine started" << LOG_END;
	
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

	const std::string map_path = settings["start-level"];
	load_level(game, map_path);

	// Game Loop
	game->start();
	while (game->is_running)
	{
		platform::WindowManager::get_window().poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();

		int loops = 0;
		float escaped_time = 0;

		while (loops < game->MAX_FRAME_SKIP && Timestamp() > game->frame_fixed_end)
		{
			// LOG_INFO << Timestamp{} -game->frame_fixed_end << LOG_END;
			physics::tick(game->TICK_DELTA_MILLIS * 0.0001f);
			physics::tick(game->TICK_DELTA_MILLIS * 0.0001f);
			game->simulate_step();
			escaped_time += game->TICK_DELTA_MILLIS;
			loops++;
		}
		AnimationManager::update(escaped_time * 0.2f);
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
