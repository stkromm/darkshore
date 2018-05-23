#include "tilemap/tile_map.h"

void tilemap::TileMap::parse(json map_source)
{
	uint32 height = map_source["height"];
	uint32 width = map_source["width"];

	for(auto& layer_source : map_source["layers"])
	{
		if(layer_source["type"] == "tilelayer")
		{
			std::shared_ptr<TileLayer> layer = std::make_shared<TileLayer>();
			layer->parse(layer_source);
			layers.push_back(layer);
		}
	}

	for(auto& property_source : map_source["properties"])
	{
		
	}

	for(auto& tileset_source : map_source["tilesets"])
	{
		std::shared_ptr<tilemap::Chipset> tile_set = std::make_shared<tilemap::Chipset>();
		tile_set->parse_tmx(tileset_source);
		tile_sets.push_back(tile_set);
	}
}
