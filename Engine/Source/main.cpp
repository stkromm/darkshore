#include "darkshore.h"

int init_platform()
{
	if (!AssetManager::init())
	{
		return -11;
	}
	if (!platform::WindowManager::init())
	{
		return -12;
	}
	if (!graphics::RenderManager::init())
	{
		return -13;
	}
	if (!graphics::SceneManager::init())
	{
		return -14;
	}
	if (!physics::init())
	{
		return -15;
	}
	if (!AnimationManager::init())
	{
		return -16;
	}
	return 0;
}
int DS_MAIN(const int argc, char** argv)
{
	
	LOG_INFO << "Vine Engine started" << LOG_END;
	
	if(init_platform() != 0)
	{
		std::cin.get();
		return -1;
	}

	auto game = new Game();
	std::ifstream config_file("../config.json");
	json settings;
	if (config_file.is_open())
		config_file >> settings;
	else
		settings = {};
	const std::string map_path = settings["start-level"];
	load_level(game, map_path);
	int benchmark_loops = 0;
	long millis = 0;
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
			physics::tick(game->TICK_DELTA_MILLIS * 0.0008f);
			game->simulate_step();
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
	graphics::SceneManager::shutdown();
	graphics::RenderManager::shutdown();
	platform::WindowManager::shutdown();

	AssetManager::clean();
	return 0;
}
