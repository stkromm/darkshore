#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>

#include "graphics/tile_map.h"
#include "object.h"

class Game {
public:
	std::shared_ptr<graphics::TileMap> tile_map;

	std::unordered_map<std::string, std::shared_ptr<GameObject>> tagged_objects;

	std::vector<std::shared_ptr<GameObject>> to_be_added;
	std::vector<std::shared_ptr<GameObject>> to_be_removed;
	std::vector<std::shared_ptr<GameObject>> objects;

	const int MAX_FRAME_SKIP = 5;
	const int TICKS_PER_SECOND = 60;
	const float TICK_DELTA_MILLIS = 1000.0f / (float)TICKS_PER_SECOND;
	const std::chrono::nanoseconds tick_delta_nanos = std::chrono::nanoseconds((int)(TICK_DELTA_MILLIS * 1000000.0f));

	bool is_running = true;
	long ticks = 0;
	std::chrono::time_point<std::chrono::steady_clock> frame_fixed_end = std::chrono::high_resolution_clock::now();

	void add_object(std::shared_ptr<GameObject> object);

	template<class C, class... _Types>
	void add_object(_Types &&... Args)
	{
		std::shared_ptr<C> component = std::make_shared<C>(std::forward<_Types>(Args)...);
		add_object(component);
	}

	template<class T>
	std::shared_ptr<T> find_by_tag(std::string tag) const
	{
		std::shared_ptr<T> obj = std::static_pointer_cast<T>(tagged_objects.find(tag)->second);
		return obj;
	}

	void load_level(std::string file_path);

	/**
	*	@return value in the interval [0,1) where means that the next frame is has not started and a value close
	*			to 1 means that the current game state is nearly the next frame.
	*/
	float get_tick_interpolation();

	void simulate_step();

	void start();
};