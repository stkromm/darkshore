#pragma once

#include "graphics/tiled_texture.h"
#include "core/json/json.h"

namespace tilemap
{

	class TileLayer
	{
		uint32_t width;
		uint32_t height;
		uint32_t tile_width;
		uint32_t tile_height;
		std::vector<uint32> tile_ids;
		std::vector<uint32> tile_states;
	public:
		TileLayer() {}
		~TileLayer();

		void parse(json layer_source);
		void update_tile_state(uint32_t o_id, uint32_t d_id);
	};
};
