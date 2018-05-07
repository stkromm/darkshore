#pragma once

#include <memory>
#include <string>

#include "core/game.h"
#include "audio/music.h"

#include "graphics/scene_manager.h"
#include "gameplay/player.h"

inline void load_level(Game* game, const std::string& name)
{
	/*dsmap::Map map;
	if (map.load(get_res_folder_path(MAP, name)))
	{
		// Check if map has a known tiled version

		for (auto& prop : map.getProperties())
		{
			if (prop.getName() == "background_music")
			{
				const std::string& path = prop.getStringValue();
				audio::play_background_music(path);
			}
		}

		int size_x = map.getTileCount().x;
		int size_y = map.getTileCount().y;
		std::cout << "size x:" << size_x << std::endl;
		std::cout << "size y:" << size_y << std::endl;

		int tile_width = map.getTileSize().x * 4;
		int tile_height = (map.getTileSize().y * 4);

		dsmap::Tileset tile_set = map.getTilesets()[0];

		std::vector<std::shared_ptr<tilemap::TileAnimationClip>> animations;

		std::cout << "Tile count x:" << tile_set.getColumnCount() << std::endl;
		std::cout << "Tile count y:" << tile_set.getTileCount() / tile_set.getColumnCount() << std::endl;
		
		auto texture = AssetManager::load_asset<graphics::Texture>(tile_set.getImagePath().substr(
			tile_set.getImagePath().find_last_of(
				'/') + 1));

		std::shared_ptr<graphics::TiledTexture> tiled_texture = std::make_shared<graphics::TiledTexture>(
			texture, tile_set.getTileSize().x, tile_set.getTileSize().y);

		std::vector<std::shared_ptr<tilemap::TileLayer>> layers;
		for (auto& generic_layer : map.getLayers())
		{
			if (generic_layer->getType() == dsmap::TileLayer::Type::Tile)
			{
				const auto& layer = dynamic_cast<dsmap::TileLayer*>(generic_layer.get());
				layers.push_back(std::make_shared<tilemap::TileLayer>(size_x, size_y, tile_width, tile_height, layer,
					tiled_texture));

			}
		}
		for (auto& tile : tile_set.getTiles())
		{
			for (auto& layer : layers)
			{
				if (!tile.animation.frames.empty())
				{
					std::vector<tilemap::TileFrame> frames;
					for (auto& frame : tile.animation.frames)
					{
						frames.push_back({ frame.tileID, float(frame.duration) });
					}
					animations.push_back(std::make_shared<tilemap::TileAnimationClip>(tile.ID, layer, frames));
				}
			}
		}

		const std::shared_ptr<tilemap::TileMap> tile_map = std::make_shared<tilemap::TileMap>(
			size_x, size_y, tiled_texture, layers, animations);

		game->add_object(tile_map);
		graphics::SceneManager::get_scene()->add_renderable(tile_map);

		game->add_object<Player>();
		for (int i = 0; i < 10; ++i)
			game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);
	}
	else
	{
		ASSERT(false);
	}*/
	//game->add_object(tile_map);
	//graphics::SceneManager::get_scene()->add_renderable(tile_map);
	game->add_object<Player>();

	for (int i = 0; i < 10; ++i)
		game->add_object<NPC>(i % 15 * 100.f, i % 20 * 100.f);
}
