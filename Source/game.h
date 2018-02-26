#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

#include "graphics/tile_map.h"
#include "object.h"
#include "player.h"

class Game {
public:
	std::shared_ptr<Player> player;
	std::shared_ptr<graphics::TileMap> tile_map;
	std::shared_ptr<graphics::Camera> camera;

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

	Game()
	{
		player = std::make_shared<Player>();
		to_be_added.push_back(player);
		graphics::SceneManager::get_scene()->get_camera()->transform->set_parent(player->get_transform());
	}

	void load_level(std::string file_path);
	/*
	@return value in the interval [0,1) where means that the next frame is has not started and a value close to 1 means that the current game state is nearly the next frame.
	*/
	float get_tick_interpolation();

	void simulate_step();

	void start();
};