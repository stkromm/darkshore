#pragma once

#include <vector>

#include "tilemap/tile_map_sprite_layer.h"
#include "graphics/renderable.h"
#include "graphics/scene.h"
#include "platform/asset.h"
#include "platform/asset_manager.h"
#include "graphics/shader.h"
#include "graphics/tiled_texture.h"

#include "physics/collision_body.h"

#include "core/object.h"

namespace graphics {
	class TileMap : public Renderable, public Asset, public GameObject {
	private:
		std::vector<std::shared_ptr<TileMapSpriteLayer>> layers;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<TiledTexture> tiled_texture;
		std::shared_ptr<Shader> shader;

		std::vector<physics::CollisionBody> collision_bodies;
		
		uint32_t size_x;
		uint32_t size_y;

		uint32_t tile_height;
		uint32_t tile_width;
	public:
		static AssetType get_resource_type()
		{
			return AssetType::MAP;
		}

		TileMap(uint32_t size_x, uint32_t size_y, std::shared_ptr<Texture> texture, std::shared_ptr<TiledTexture> texture2, std::vector<std::shared_ptr<TileMapSpriteLayer>> layers) : layers(layers), size_x(size_x), size_y(size_y), tiled_texture(texture2), texture(texture)
		{
			transform = std::make_shared<Transform>();
			transform->translate({ -260,-160 });
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			shader = AssetManager::load_asset<Shader>("basic.shader");
		}
		~TileMap()
		{
			std::cout << "Delete tilemap" << std::endl;
		}
		void draw(const float interpolation, Renderer& renderer) const override
		{
			for (auto& layer : layers) {
				shader->bind();
				shader->set_uniform_mat4x4("pr_matrix", graphics::SceneManager::get_scene()->get_camera()->get_projection());
				shader->set_uniform_mat4x4("vw_matrix", transform->get_local_to_world());
				texture->bind();
				shader->set_uniform_1i("tex", 0);
				layer->draw(renderer, shader.get());
			}
		}

		std::string to_string() const
		{
			std::stringstream sstream;
			sstream << "TileMap(size:(" << size_x << "," << size_y << "),layerCount:" << layers.size() << ")";
			return std::move(sstream.str());
		}
	};
};