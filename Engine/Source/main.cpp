#include "darkshore.h"
#include "tilemap/tilemap.h"

using namespace ds;

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
	if (!scene::RenderManager::init())
	{
		return -13;
	}
	if (!scene::SceneManager::init())
	{
		return -14;
	}
	if (!gui::GuiManager::init())
	{
		return -15;
	}
	if (!physics::init())
	{
		return -16;
	}
	if (!AnimationManager::init())
	{
		return -17;
	}
	return 0;
}
int DS_MAIN(const int argc, char** argv)
{

	LOG_INFO << "Vine Engine started" << LOG_END;

	if (init_platform() != 0)
	{
		std::cin.get();
		return -10;
	}

	auto game = new game::Game();
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
	scene::SceneManager::get_scene()->add_renderable(std::make_shared<graphics::TileMap>("map.tmx"));
	while (game->is_running)
	{
		// glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
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
		scene::SceneManager::get_scene()->render(game->get_tick_interpolation());
		gui::GuiManager::get_gui()->render(game->get_tick_interpolation());
		platform::WindowManager::get_window().swap_buffers();
	}

	delete game;

	AnimationManager::shutdown();
	physics::shutdown();
	scene::SceneManager::shutdown();
	scene::RenderManager::shutdown();
	gui::GuiManager::shutdown();
	platform::WindowManager::shutdown();

	AssetManager::clean();
	return 0;
}
