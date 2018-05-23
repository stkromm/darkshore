#pragma once

#include <string>

#include "game/game.h"
#include "audio/music.h"

#include "gameplay/player.h"

inline void load_level(Game* game, const std::string& name)
{
	//std::shared_ptr<tilemap::TileMap> tilemap = AssetManager::load_asset<tilemap::TileMap>(name);
	//game->add_object<tilemap::TileMapEntity>(tilemap);
	game->add_object<Player>();

	for (int i = 0; i < 100; ++i)
		game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);
}
