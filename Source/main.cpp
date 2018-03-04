#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "json.h"

#include "scripting/script.h"
#include "graphics/render_manager.h"
#include "platform/window.h"
#include "platform/asset.h"
#include "physics/physics.h"
#include "animation_manager.h"

#include "game.h"
#include "player.h"

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
	if (!physics::PhysicSimulation::init())
	{
		return -1;
	}
	if (!AnimationManager::init())
	{
		return -1;
	}

	Game* game = new Game();
	std::cout << "Load level" << std::endl;
	std::string map_path = settings["start-level"];
	game->load_level(map_path);

	game->add_object<Player>();
	for(int i = 0; i < 10; ++i)
	game->add_object<NPC>(i%15 * 100.f, i%20 * 100.f);

	// Game Loop
	int loops = 0;

	game->start();
	while (game->is_running) {
		platform::WindowManager::get_window().poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();

		loops = 0;
		float escaped_time = 0;

		while (loops < game->MAX_FRAME_SKIP &&
			std::chrono::high_resolution_clock::now() > game->frame_fixed_end)
		{
			game->simulate_step();
			physics::PhysicSimulation::tick(game->TICK_DELTA_MILLIS * 0.001f);
			escaped_time += game->TICK_DELTA_MILLIS;
			loops++;
		}

		AnimationManager::update(escaped_time);
		graphics::SceneManager::get_scene()->render(game->get_tick_interpolation());
		platform::WindowManager::get_window().swap_buffers();
	}

	delete game;

	AnimationManager::shutdown();
	physics::PhysicSimulation::shutdown();
	scripting::ScriptManager::shutdown();
	graphics::SceneManager::shutdown();
	graphics::RenderManager::shutdown();
	platform::WindowManager::shutdown();

	AssetManager::clean();
	return 0;
}