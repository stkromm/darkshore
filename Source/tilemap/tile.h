#pragma once
#include <vector>

class Tile {
	uint32_t id;
	std::vector<uint32_t> collision_bodies;
};