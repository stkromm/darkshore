#pragma once

#include <memory>

#include "tmxlite/TileLayer.hpp"
#include "graphics/index_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"
#include "graphics/renderer.h"
#include "graphics/sprite_vertex.h"
#include "graphics/texture.h"
#include "graphics/tiled_texture.h"

namespace graphics
{
	struct Tile
	{
		uint32_t original_id;
		uint32_t displayed_id;
		int x;
		int y;
	};
	struct TileMapSpriteLayer
	{
		uint32_t width;
		uint32_t height;
		uint32_t tile_width;
		uint32_t tile_height;

		std::vector<Tile> tiles;

		std::unique_ptr<VertexBuffer> vertex_buffer_position;
		std::unique_ptr<VertexBuffer> vertex_buffer_uvs;
		std::unique_ptr<VertexBuffer> vertex_buffer_color;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::shared_ptr<TiledTexture> tiled_texture;

		TileMapSpriteLayer(const uint32_t size_x, const uint32_t size_y,
			const uint32_t tile_width, const uint32_t tile_height, tmx::TileLayer* layer,
			std::shared_ptr<TiledTexture>& tiled_texture, uint32_t columns) : width(size_x), height(size_y),
			tile_width(tile_width), tile_height(tile_height), tiled_texture(tiled_texture)
		{
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;

			uint32_t drawn_tiles = 0;

			for (uint32_t i = 0; i < size_x; ++i)
			{
				for (uint32_t j = 0; j < size_y; ++j)
				{
					const uint32_t index = j * size_x + i;
					if (layer->getTiles()[index].ID != 0)
					{
						indices.push_back(drawn_tiles * 4 + 0);
						indices.push_back(drawn_tiles * 4 + 1);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 3);
						indices.push_back(drawn_tiles * 4 + 0);

						const uint32_t color = 0x000000FF;
						const auto x = float(tile_width * i);
						const auto y = float(tile_height * (size_y - j));

						const uint32_t id = layer->getTiles()[index].ID - 1;

						tiles.push_back({
						id, id, int(i), int(j)
							});
						const TexturePatch patch = tiled_texture->get_texture_patch(id);
						const Vertex a =
						{
							0 + x, 0 + y,
							patch.x1, patch.y1,
							color
						};
						const Vertex b =
						{
							tile_width + x, 0 + y,
							patch.x2, patch.y1,
							color
						};
						const Vertex c =
						{
							tile_width + x, tile_height + y,
							patch.x2, patch.y2,
							color
						};
						const Vertex d =
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
			vertex_buffer_position = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Vertex) * vertices.size());

			VertexBufferLayout vb_layout_pos;
			vb_layout_pos.push<float>(2);
			vb_layout_pos.push<float>(2);
			vb_layout_pos.push<uint32_t>(1);

			vertex_array->add_buffer(*vertex_buffer_position, vb_layout_pos);

			index_buffer = std::make_unique<IndexBuffer>(indices);
		}

		~TileMapSpriteLayer()
		{
			std::cout << "Delete layer" << std::endl;
		}

		void update_tile_state(const uint32_t o_id, const uint32_t d_id)
		{
			bool success = false;
			for (auto& tile : tiles)
			{
				if (tile.original_id == o_id)
				{
					success = true;
					tile.displayed_id = d_id;
				}
			}
			if(success)
			{
				update_tiles();
			}
		}

		void update_tiles()
		{
			std::vector<Vertex> vertices;
			for (auto& tile : tiles)
			{
				const uint32_t color = 0x000000FF;
				const auto x = float(tile_width * tile.x);
				const auto y = float(tile_height * (height - tile.y));
				const uint32_t id = tile.displayed_id;
				const TexturePatch patch = tiled_texture->get_texture_patch(id);
				const Vertex a =
				{
					0 + x, 0 + y,
					patch.x1, patch.y1,
					color
				};
				const Vertex b =
				{
					tile_width + x, 0 + y,
					patch.x2, patch.y1,
					color
				};
				const Vertex c =
				{
					tile_width + x, tile_height + y,
					patch.x2, patch.y2,
					color
				};
				const Vertex d =
				{
					0 + x, tile_height + y,
					patch.x1, patch.y2,
					color
				};
				vertices.push_back(a);
				vertices.push_back(b);
				vertices.push_back(c);
				vertices.push_back(d);
			}
			vertex_array->bind();
			vertex_buffer_position->update(vertices.data(), sizeof(Vertex) * vertices.size());
		}

		void draw(Renderer& renderer, Shader* shader) const
		{
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};
};
