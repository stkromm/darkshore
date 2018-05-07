#pragma once

#include <utility>
#include <vector>

#include "tilemap/tile_map_grid_layer.h"
#include "graphics/renderable.h"
#include "graphics/scene.h"
#include "platform/asset.h"
#include "platform/asset_manager.h"
#include "graphics/shader.h"
#include "graphics/tiled_texture.h"
#include "platform/asset_types.h"

#include "physics/collision_body.h"

#include "core/object.h"
#include "tile_animation_clip.h"
#include "gameplay/sprite_animation_component.h"
#include "gameplay/player.h"
#include "graphics/scene_manager.h"

namespace tilemap
{
	class TileMap : public graphics::Renderable, public Asset, public Entity
	{
	private:
		std::vector<std::shared_ptr<TileLayer>> layers;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<graphics::TiledTexture> tiled_texture;
		std::shared_ptr<graphics::Shader> shader;

		std::vector<physics::CollisionBody> collision_bodies;
		std::vector<std::shared_ptr<TileAnimationClip>> animations;

		uint32_t size_x;
		uint32_t size_y;
	public:
		static AssetType get_resource_type()
		{
			return MAP;
		}

		TileMap(uint32_t size_x, uint32_t size_y,
			std::shared_ptr<graphics::TiledTexture> texture,
			std::vector<std::shared_ptr<TileLayer>> layers, std::vector<std::shared_ptr<TileAnimationClip>> animations);
		~TileMap();

		void on_spawn() override;
		void tick() override;
		void draw(float interpolation) const override;

		void set_render_window(const float x, const float y);

		std::string to_string() const
		{
			std::stringstream sstream;
			sstream << "TileMap(size:(" << size_x << "," << size_y << "),layerCount:" << layers.size() << ")";
			return sstream.str();
		}
	};
};
