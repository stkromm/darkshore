#pragma once

#include "json.h"

#include "tile_layer.h"
#include "chipset.h"

namespace tilemap
{
	class TileMap
	{
		uint32 width;
		uint32 height;
		int32 offset_x;
		int32 offset_y;

		std::vector<std::shared_ptr<TileLayer>> layers;
		std::vector<std::shared_ptr<Chipset>> tile_sets;

	public:
		void parse(json map_source);
	};
}
