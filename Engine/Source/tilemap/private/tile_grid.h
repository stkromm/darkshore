#pragma once
#include <vector>

#include "tilemap/private/tile.h"

namespace tilemap
{
	struct TileGrid
	{
		TileGrid(const uint32_t width, const uint32_t height, const uint32_t tile_width, const uint32_t tile_height, const std::vector<Tile> tiles)
			: width(width), height(height), tile_width(tile_width), tile_height(tile_height), tiles(tiles)
		{}
		uint32_t width;
		uint32_t height;
		uint32_t tile_width;
		uint32_t tile_height;
		std::vector<Tile> tiles;
	};
}
