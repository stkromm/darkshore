#pragma once

#include "core/json/json.h"
#include "core/types.h"
#include "terrain.h"
#include "tile_animation_clip.h"

namespace tilemap
{
	struct ChipsetTile
	{
		uint32 terrain_id;
	};
	class Chipset
	{
	private:
		std::string name;
		std::string texture_path;

		std::vector<Terrain> terrains;

		std::vector<TileAnimationClip> animations;

		std::vector<ChipsetTile> tiles;

		uint32 tile_height = 0;
		uint32 tile_width = 0;

	public:
		void parse_tmx(json tileset_source);
		std::shared_ptr<ds::graphics::TiledTexture> get_texture() const;
		uint32 get_tile_count_width() const;
		uint32 get_tile_count_height() const;
	};
}
