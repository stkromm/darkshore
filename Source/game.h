#pragma once

#include <chrono>
#include <vector>
#include <algorithm>

#include "object.h"

class Bot : public object {
public:
	int count = 0;

	Bot() {
	}

	void on_spawn() override {
	}
	void tick() override {
		if (is_destroyed) return;
		count++;

		if (count > 200) {
			destroy();
		}
	}

	void on_destroy() override {}
};

class Game {
public:
	std::vector<object*> to_be_added;
	std::vector<object*> to_be_removed;
	std::vector<object*> objects;

	const int MAX_FRAME_SKIP = 5;
	const int TICKS_PER_SECOND = 60;
	const float TICK_DELTA_MILLIS = 1000.0f / (float)TICKS_PER_SECOND;
	const std::chrono::nanoseconds tick_delta_nanos = std::chrono::nanoseconds((int)(TICK_DELTA_MILLIS * 1000000.0f));

	bool is_running = true;
	long ticks = 0;
	std::chrono::time_point<std::chrono::steady_clock> frame_fixed_end = std::chrono::high_resolution_clock::now();

	Game()
	{
		to_be_added.push_back(new Bot());
	}

	/*
	@return value in the interval [0,1) where means that the next frame is has not started and a value close to 1 means that the current game state is nearly the next frame.
	*/
	float get_tick_interpolation() 
	{
		const auto remaining_tick_duration = frame_fixed_end - std::chrono::high_resolution_clock::now();
		return 1 - (remaining_tick_duration.count() / 1000000.0f) / TICK_DELTA_MILLIS;
	}

	void simulate_step() 
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
				delete obj;
			}
		}
		to_be_removed.clear();
		ticks++;
		std::cout << "Tick #" << ticks << " duration:" << std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - step_start).count() / 1000000.f << std::endl;
	}

	void start() {
		frame_fixed_end = std::chrono::high_resolution_clock::now();
	}
};