#include "tilemap/chipset.h"

void tilemap::Chipset::parse_tmx(json tileset_source)
{
	const std::string _name = tileset_source["name"];
	name = _name;
	const std::string _texture_path = tileset_source["image"];
	texture_path = _texture_path;
	uint32 _tile_height = tileset_source["tileheight"];
	uint32 _tile_width = tileset_source["tilewidth"];

	const uint32 tile_count = tileset_source["tilecount"];
	tiles.reserve(tile_count);

	
	auto tiles_definitions = tileset_source["tiles"];
	for(json::iterator it = tiles_definitions.begin(); it != tiles_definitions.end(); ++it)
	{
		uint32 index = std::stoi(it.key());
		auto& tile_definition = it.value();
		// Get terrain
		
		if(tile_definition.find("animation") != tile_definition.end())
		{
			// Is an animated tile
		}
	}
}
