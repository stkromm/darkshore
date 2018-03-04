#pragma once

#include <memory>
#include <string>

#include "audio/music.h"

#include "math/vec2.h"
#include "platform/file_handle.h"
#include "platform/asset.h"

#include "tiled_texture.h"
#include "sprite.h"

#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

namespace graphics {

	struct TileMapLayer {
		unsigned int width;
		unsigned int height;

		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;

		TileMapLayer(unsigned int size_x, unsigned int size_y, unsigned int tile_width, unsigned int tile_height, tmx::TileLayer* layer, std::shared_ptr<TiledTexture>& tiled_texture, unsigned int columns)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			unsigned int drawn_tiles = 0;

			for (unsigned int i = 0; i < size_x; ++i)
			{
				for (unsigned int j = 0; j < size_y; ++j)
				{
					unsigned int index = j * size_x + i;
					if (layer->getTiles()[index].ID != 0)
					{
						indices.push_back(drawn_tiles * 4 + 0);
						indices.push_back(drawn_tiles * 4 + 1);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 3);
						indices.push_back(drawn_tiles * 4 + 0);

						unsigned int color = 0x000000FF;
						float x = (float)(tile_width * i);
						float y = (float)(tile_height * (size_y - j));

						unsigned int id = layer->getTiles()[index].ID - 1;

						TexturePatch patch = tiled_texture->get_texture_patch(id);
						Vertex a =
						{
							0 + x, 0 + y,
							patch.x1, patch.y1,
							color
						};
						Vertex b =
						{
							tile_width + x, 0 + y,
							patch.x2, patch.y1,
							color
						};
						Vertex c =
						{
							tile_width + x, tile_height + y,
							patch.x2, patch.y2,
							color
						};
						Vertex d =
						{
							0 + x, tile_height + y,
							patch.x1, patch.y2,
							color
						};

						vertices.push_back(a);
						vertices.push_back(b);
						vertices.push_back(c);
						vertices.push_back(d);

						drawn_tiles++;
					}
				}
			}

			vertex_array = std::make_unique<VertexArray>();
			vertex_buffer = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Vertex) * vertices.size());
			index_buffer = std::make_unique<IndexBuffer>(indices);

			VertexBufferLayout vb_layout;
			vb_layout.push<float>(2);
			vb_layout.push<float>(2);
			vb_layout.push<unsigned int>(1);

			vertex_array->add_buffer(*vertex_buffer, vb_layout);
		}

		~TileMapLayer()
		{
			std::cout << "Delete layer" << std::endl;
		}

		void draw(Renderer& renderer, Shader* shader) const
		{
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};

	class TileMap : public Renderable, public Asset {
	private:
		std::vector<std::unique_ptr<TileMapLayer>> layers;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<TiledTexture> tiled_texture;
		std::shared_ptr<Shader> shader;

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
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			shader = AssetManager::load_asset<Shader>("basic.shader");

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
						audio::play_background_music(path);
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

				texture = AssetManager::load_asset<Texture>(tile_set.getImagePath().substr(tile_set.getImagePath().find_last_of("/")+1));

				tiled_texture = std::make_shared<TiledTexture>(texture, tile_set.getTileSize().x, tile_set.getTileSize().y);

				for (auto& generic_layer : map.getLayers())
				{
					if (generic_layer->getType() == tmx::TileLayer::Type::Tile)
					{
						const auto& layer = dynamic_cast<tmx::TileLayer*> (generic_layer.get());
						layers.push_back(std::make_unique<TileMapLayer>(size_x, size_y, tile_width, tile_height, layer, tiled_texture, tile_set.getColumnCount()));
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
	};
}