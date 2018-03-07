#include "game.h"

float Game::get_tick_interpolation()
{
	const auto remaining_tick_duration = frame_fixed_end - std::chrono::high_resolution_clock::now();
	return (remaining_tick_duration.count() * 0.0000001f) / TICK_DELTA_MILLIS;
}

void Game::add_object(std::shared_ptr<GameObject> object)
{
	for (auto& obj : objects) 
	{
		if (obj == object) return;
	}
	tagged_objects.erase(object->get_tag());
	to_be_added.push_back(object);
	if (object->get_tag() != "")
	{
		tagged_objects[object->get_tag()] = object;
	}
}

void Game::simulate_step()
{
	auto step_start = std::chrono::high_resolution_clock::now();
	frame_fixed_end += tick_delta_nanos;
	for (auto& obj : to_be_added) {
		obj->set_game(this);
		objects.push_back(obj);
		obj->on_spawn();
	}
	to_be_added.clear();

#pragma omp parallel for schedule(dynamic)
	for(int i = 0; i < (int)objects.size(); ++i)
	{
		objects[i]->self_tick();
	}
	for (auto& obj : objects) {
		if (obj->is_destroyed) {
			to_be_removed.push_back(obj);
		}
		else {
			obj->tick();
		}
	}
	if (!to_be_removed.empty()) {
		for (auto& obj : to_be_removed) {
			obj->on_destroy();
			objects.erase(std::find(objects.begin(), objects.end(), obj));
		}
	}
	to_be_removed.clear();
	ticks++;
}

void Game::start() {
	frame_fixed_end = std::chrono::high_resolution_clock::now();
}