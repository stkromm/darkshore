#pragma once

#include <utility>
#include <vector>

#include "tilemap/tile_map_sprite_layer.h"
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

namespace graphics
{
	class TileMap : public Renderable, public Asset, public Entity
	{
	private:
		std::vector<std::shared_ptr<TileMapSpriteLayer>> layers;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<TiledTexture> tiled_texture;
		std::shared_ptr<Shader> shader;

		std::vector<physics::CollisionBody> collision_bodies;
		std::vector<std::shared_ptr<TileAnimationClip>> animations;

		uint32_t size_x;
		uint32_t size_y;

	public:
		static AssetType get_resource_type()
		{
			return MAP;
		}

		TileMap(const uint32_t size_x, const uint32_t size_y, std::shared_ptr<Texture> texture,
			std::shared_ptr<TiledTexture> texture2,
			std::vector<std::shared_ptr<TileMapSpriteLayer>> layers, std::vector<std::shared_ptr<TileAnimationClip>> animations) : layers(std::move(layers)), texture(
				std::move(texture)), animations(animations),
			tiled_texture(std::move(texture2)), size_x(size_x),
			size_y(size_y)
		{
			transform = std::make_shared<Transform>();
			transform->translate({ -260, -160 });
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			shader = AssetManager::load_asset<Shader>("basic.shader");

		}

		~TileMap()
		{
			std::cout << "Delete tilemap" << std::endl;
		}

		void on_spawn() override
		{
			for (auto& animation : animations)
			{
				std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
				animation_state_machine->add_state({ "tile_anim", animation });
				add_component<AnimationComponent>(animation_state_machine);
			}
		}
		void draw(const float interpolation, Renderer& renderer) const override
		{
			for (auto& layer : layers)
			{
				shader->bind();
				shader->set_uniform_mat4x4("pr_matrix", SceneManager::get_scene()->get_camera()->get_projection());
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
			return sstream.str();
		}
	};
};
