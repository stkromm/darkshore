#pragma once

#include <memory>
#include <string>

#include "audio/music.h"

#include "core/math/vec2.h"
#include "platform/resource_handle.h"
#include "platform/asset.h"

#include "graphics/tiled_texture.h"
#include "scene/sprite.h"

#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "scene/sprite_batch.h"
#include "animation/animation_manager.h"

namespace ds {
	namespace graphics {
		struct Frame
		{
			ds::graphics::TexturePatch patch;
			float duration;
		};

		class AnimatedTile : public AnimationClip {
		public:
			std::vector<Frame> frames;
			uint_fast32_t frame_id = 0;
			TexturePatch patch;

			AnimatedTile(std::vector<Frame> frames): frames(frames) {
				duration = 0;
				for (auto& frame : frames)
				{
					duration += frame.duration;
				}
				AnimatedTile::reset();
			}

			virtual void on_frame_update(const uint_fast32_t frame_id)
			{
				patch = frames[frame_id].patch;
			}

			void reset() override
			{
				remaining_clip_time = duration;
				frame_id = 0;
				on_frame_update(frame_id);
			}

			void update(const float delta_millis) override
			{
				remaining_clip_time -= delta_millis;
				float frame_end_time = 0;
				const float escaped_time = duration - remaining_clip_time;

				for (uint_fast32_t i = 0; i < frames.size(); ++i)
				{
					Frame& frame = frames[i];
					frame_end_time += frame.duration;
					if (frame_end_time > escaped_time)
					{
						if (i != frame_id)
						{
							frame_id = i;
							on_frame_update(frame_id);
						}
						return;
					}
				}
				frame_id = 0;
				on_frame_update(frame_id);
			}
		};
		struct AnimatedTilePosition {
			ds::Vec2<float> pos;
			std::shared_ptr<AnimatedTile> animation;
		};
		struct TileMapLayer {
			unsigned int width;
			unsigned int height;
			unsigned int tile_width;
			unsigned int tile_height;

			std::unique_ptr<scene::DynamicSpriteBatch> dynamic_sprite_batch;
			std::unique_ptr<scene::StaticSpriteBatch> sprite_batch;
			std::shared_ptr<TiledTexture> tiled_texture;
			std::vector<std::shared_ptr<AnimationStateMachine>> active_animations;
			std::unordered_map<uint32, std::shared_ptr<AnimatedTile>> tile_animations;
			std::vector<AnimatedTilePosition> dynamic_tiles;
			tmx::TileLayer* layer;

			TileMapLayer(std::map<uint32, tmx::Tileset::Tile> animated_tiles, unsigned int size_x, unsigned int size_y, unsigned int tile_width, unsigned int tile_height, tmx::TileLayer* layer, std::shared_ptr<TiledTexture>& tiled_texture, unsigned int columns)
			{
				this->layer = layer;
				this->sprite_batch = std::make_unique<scene::StaticSpriteBatch>(size_x * size_y);
				this->dynamic_sprite_batch = std::make_unique<scene::DynamicSpriteBatch>();
				this->tiled_texture = tiled_texture;
				this->width = width;
				this->height = height;
				this->tile_width = tile_width;
				this->tile_height = tile_height;
				unsigned int drawn_tiles = 0;

				for (unsigned int i = 0; i < size_x; ++i)
				{
					for (unsigned int j = 0; j < size_y; ++j)
					{
						unsigned int index = j * size_x + i;
						auto tile = layer->getTiles()[index];
						unsigned int color = 0x000000FF;
						float x = (float)(tile_width * i);
						float y = (float)(tile_height * (size_y - j));
						unsigned int id = tile.ID - 1;
						auto animated_tile = animated_tiles.find(tile.ID);
						if (animated_tile != animated_tiles.end()) {
							auto exists = tile_animations.find(tile.ID);
							if (exists == tile_animations.end()) {
								// Create animation
								std::vector<Frame> frames;
								for (auto frame : animated_tile->second.animation.frames) {
									frames.push_back({ tiled_texture->get_texture_patch(frame.tileID - 1), 1.0f * frame.duration });
								}
								const std::shared_ptr<AnimatedTile> clip = std::make_shared<AnimatedTile>(frames);
								tile_animations.emplace(tile.ID, clip);
								std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
								animation_state_machine->add_state({ "tile", clip });
								AnimationManager::add_animation(animation_state_machine);
								active_animations.push_back(animation_state_machine);
								this->dynamic_tiles.push_back({ { x, y }, clip });
							}
							else {
								this->dynamic_tiles.push_back({ { x, y }, exists->second });
							}
						}
						else if (tile.ID != 0)
						{
							TexturePatch patch = tiled_texture->get_texture_patch(id);
							this->sprite_batch->push(0, patch, ds::Vec2<float>(x, y), ds::Vec2<float>(tile_width, tile_height), color);
						}
					}
				}

			}

			~TileMapLayer()
			{
				std::cout << "Delete layer" << std::endl;
				for (auto active_animation : active_animations) {
					AnimationManager::remove_animation(active_animation);
				}
			}

			void draw() const
			{
				this->tiled_texture->get_texture()->bind();
				this->sprite_batch->flush();

				for (auto& dynamic_tile : dynamic_tiles) {
					this->dynamic_sprite_batch->submit(1, dynamic_tile.animation->patch, dynamic_tile.pos, { 1.0f * tile_width, 1.0f * tile_height }, 0);
				}
				this->dynamic_sprite_batch->flush();
			}
		};

		class TileMap : public scene::Renderable, public Asset {
		private:
			std::vector<std::unique_ptr<TileMapLayer>> layers;
			std::shared_ptr<Transform> transform;
			std::shared_ptr<TextureAsset> texture;
			std::shared_ptr<TiledTexture> tiled_texture;
			std::shared_ptr<ShaderAsset> shader;

			unsigned int size_x;
			unsigned int size_y;

			unsigned int tile_height;
			unsigned int tile_width;
		public:
			static AssetType get_resource_type()
			{
				return AssetType::MAP;
			}

			TileMap(std::string map_name)
			{
				transform = std::make_shared<Transform>();
				transform->translate({ -260,-160 });
				std::vector<scene::Vertex> vertices;
				std::vector<unsigned int> indices;
				shader = AssetManager::load_asset<ShaderAsset>("sprite.shader");

				tmx::Map map;
				if (map.load(get_res_folder_path(AssetType::MAP, map_name)))
				{
					// Check if map has a known tiled version
					ASSERT(map.getOrientation() == tmx::Orientation::Orthogonal);
					ASSERT(map.getRenderOrder() == tmx::RenderOrder::RightUp);

					for (auto& prop : map.getProperties())
					{
						if (prop.getName() == "background_music")
						{
							std::string path = prop.getStringValue();
						}
					}

					size_x = map.getTileCount().x;
					size_y = map.getTileCount().y;
					std::cout << "size x:" << size_x << std::endl;
					std::cout << "size y:" << size_y << std::endl;

					tile_width = map.getTileSize().x * 4;
					tile_height = (map.getTileSize().y * 4);

					tmx::Tileset tile_set = map.getTilesets()[0];
					std::cout << "Tile count x:" << tile_set.getColumnCount() << std::endl;
					std::cout << "Tile count y:" << tile_set.getTileCount() / tile_set.getColumnCount() << std::endl;

					auto texture_name = tile_set.getImagePath().substr(tile_set.getImagePath().find_last_of("/") + 1);
					texture = AssetManager::load_asset<TextureAsset>(texture_name);

					tiled_texture = std::make_shared<TiledTexture>(texture->texture, tile_set.getTileSize().x, tile_set.getTileSize().y);
					for (auto& generic_layer : map.getLayers())
					{
						if (generic_layer->getType() == tmx::TileLayer::Type::Tile)
						{
							const auto& layer = dynamic_cast<tmx::TileLayer*> (generic_layer.get());
							auto animated_tiles = map.getAnimatedTiles();
							layers.push_back(std::make_unique<TileMapLayer>(std::move(animated_tiles), size_x, size_y, tile_width, tile_height, layer, tiled_texture, tile_set.getColumnCount()));
						}
					}

				}
				else
				{
					ASSERT(false);
				}
			}
			~TileMap()
			{
				std::cout << "Delete tilemap" << std::endl;
			}
			void draw(const float interpolation) const override
			{
				for (auto& layer : layers) {
					layer->draw();
				}
			}
		};
	}
}