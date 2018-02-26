#include "game.h"

void Game::load_level(std::string file_path)
{
	tile_map = std::make_shared<graphics::TileMap>(file_path);
	graphics::SceneManager::get_scene()->add_renderable(tile_map);
}

float Game::get_tick_interpolation()
{
	const auto remaining_tick_duration = frame_fixed_end - std::chrono::high_resolution_clock::now();
	return 1 - (remaining_tick_duration.count() / 1000000.0f) / TICK_DELTA_MILLIS;
}

void Game::simulate_step()
{
	auto step_start = std::chrono::high_resolution_clock::now();
	frame_fixed_end += tick_delta_nanos;
	for (auto obj : to_be_added) {
		objects.push_back(obj);
		obj->on_spawn();
	}
	to_be_added.clear();
	for (auto obj : objects) {
		if (obj->is_destroyed) {
			to_be_removed.push_back(obj);
		}
		else {
			obj->tick();
		}
	}
	if (to_be_removed.size() != 0) {
		for (auto obj : to_be_removed) {
			obj->on_destroy();
			objects.erase(std::find(objects.begin(), objects.end(), obj));
		}
	}
	to_be_removed.clear();
	ticks++;
	std::cout << "Tick #" << ticks << " duration:" << std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - step_start).count() / 1000000.f << std::endl;
}

void Game::start() {
	frame_fixed_end = std::chrono::high_resolution_clock::now();
}