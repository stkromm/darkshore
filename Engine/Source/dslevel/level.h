#pragma once

#include <string>

#include "tilemap/tile_map.h"

struct PlayerStartpoint
{
	float x; 
	float y;
};

struct Level
{
	std::string name;
	std::string background_music_name;
	std::string start_script_name;
	
	PlayerStartpoint startpoint;

	std::shared_ptr<tilemap::TileMap> map;
};
