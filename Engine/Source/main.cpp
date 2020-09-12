#include "darkshore.h"

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
	byte game_state = 0;
	auto text = std::make_shared<gui::Text>("");
	auto start_button = std::reinterpret_pointer_cast<gui::GuiElement>(text);
	gui::GuiManager::get_gui()->add_element(start_button);
	float average_frame_duration = 0;
	Timestamp last_frame = Timestamp();
	while (game->is_running)
	{
		last_frame = Timestamp();
		std::ostringstream ss;
		ss << average_frame_duration;
		text->set_text(std::string(ss.str()));
		// glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		platform::WindowManager::get_window().poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();
		physics::tick(game->TICK_DELTA_MILLIS);
		game->simulate_step();
		AnimationManager::update(game->TICK_DELTA_MILLIS);
		scene::SceneManager::get_scene()->render(game->get_tick_interpolation());
		gui::GuiManager::get_gui()->render(game->get_tick_interpolation());
		auto frame_duration = Timestamp() - last_frame;
		average_frame_duration = average_frame_duration * 0.8f + frame_duration * 0.2f;
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
