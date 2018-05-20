#pragma once

#include <utility>
#include <vector>

#include "graphics/shader.h"
#include "graphics/tiled_texture.h"

#include "physics/collision_body.h"
#include "gameplay/player.h"

namespace tilemap
{
	class TileMapEntity : public Entity
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

		TileMapEntity(tilemap::TileMap tilemap);
		~TileMapEntity();

		void on_spawn() override;
		void tick() override;

		void set_render_window(const float x, const float y);

		std::string to_string() const
		{
			std::stringstream sstream;
			sstream << "TileMap(size:(" << size_x << "," << size_y << "),layerCount:" << layers.size() << ")";
			return sstream.str();
		}
	};
};
