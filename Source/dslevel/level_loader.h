#pragma once

#include <memory>
#include <string>

#include "core/game.h"
#include "audio/music.h"

#include "graphics/scene_manager.h"
#include "gameplay/player.h"
#include "tilemap/tile_map.h"
#include "gameplay/tile_map_entity.h"

inline void load_level(Game* game, const std::string& name)
{
	std::shared_ptr<tilemap::TileMap> tilemap = AssetManager::load_asset<tilemap::TileMap>(name);
	game->add_object<tilemap::TileMapEntity>(tilemap);
	game->add_object<Player>();

	for (int i = 0; i < 10; ++i)
		game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);
}
