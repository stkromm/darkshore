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

	struct TileMapGridLayer
	{
		uint32_t width;
		uint32_t height;
		uint32_t tile_width;
		uint32_t tile_height;

		uint32_t render_window_width = 40;
		uint32_t render_window_height = 21;
		float render_window_x = 0;
		float render_window_y = 0;

		std::vector<Tile> tiles;

		std::unique_ptr<VertexBuffer> vertex_buffer_position;
		std::unique_ptr<VertexBuffer> vertex_buffer_uvs;
		std::unique_ptr<VertexBuffer> vertex_buffer_color;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::shared_ptr<TiledTexture> tiled_texture;

		TileMapGridLayer(const uint32_t size_x, const uint32_t size_y,
			const uint32_t tile_width, const uint32_t tile_height, tmx::TileLayer* layer,
			std::shared_ptr<TiledTexture>& tiled_texture, uint32_t columns)
			: width(size_x), height(size_y), tile_width(tile_width), tile_height(tile_height), tiled_texture(tiled_texture)
		{
			std::vector<float> positions;
			positions.reserve(8 * render_window_width * render_window_height);
			std::vector<float> uvs;
			uvs.resize(8 * render_window_width * render_window_height);
			std::vector<uint32_t> colors;
			colors.resize(4 * render_window_width * render_window_height);

			tiles.resize(size_x * size_y);
			for (uint32_t i = 0; i < size_x; ++i)
			{
				for (uint32_t j = 0; j < size_y; ++j)
				{
					const uint32_t index = j * size_x + i;
					const uint32_t id = layer->getTiles()[index].ID - 1;
					tiles[index] = {
						id, id, int(i), int(j)
					};
				}
			}

			std::vector<uint32_t> indices;
			uint32_t drawn_tiles = 0;
			for (uint32_t i = 0; i < render_window_width; ++i)
			{
				const auto x = float(tile_width * i);
				for (uint32_t j = 0; j < render_window_height; ++j)
				{
					indices.push_back(drawn_tiles * 4 + 0);
					indices.push_back(drawn_tiles * 4 + 1);
					indices.push_back(drawn_tiles * 4 + 2);
					indices.push_back(drawn_tiles * 4 + 2);
					indices.push_back(drawn_tiles * 4 + 3);
					indices.push_back(drawn_tiles * 4 + 0);

					const auto y = float(tile_height * (render_window_height - j));

					positions.push_back(x);
					positions.push_back(y);

					positions.push_back(x + tile_width);
					positions.push_back(y);

					positions.push_back(x + tile_width);
					positions.push_back(y + tile_height);

					positions.push_back(x);
					positions.push_back(y + tile_height);

					drawn_tiles++;
				}
			}

			vertex_array = std::make_unique<VertexArray>();

			vertex_buffer_position = std::make_unique<VertexBuffer>(positions.data(), sizeof(float) * positions.size());
			VertexBufferLayout vb_layout_pos;
			vb_layout_pos.push<float>(2);
			vertex_array->add_buffer(*vertex_buffer_position, vb_layout_pos);

			vertex_buffer_uvs = std::make_unique<VertexBuffer>(uvs.data(), sizeof(float) * uvs.size());
			VertexBufferLayout vb_layout_uvs;
			vb_layout_uvs.push<float>(2);
			vertex_array->add_buffer(*vertex_buffer_uvs, vb_layout_uvs);

			vertex_buffer_color = std::make_unique<VertexBuffer>(colors.data(), sizeof(uint32_t) * colors.size());
			VertexBufferLayout vb_layout_col;
			vb_layout_col.push<uint32_t>(1);
			vertex_array->add_buffer(*vertex_buffer_color, vb_layout_col);

			index_buffer = std::make_unique<IndexBuffer>(indices);
		}

		~TileMapGridLayer()
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
			if (success)
			{
				update_tiles();
			}
		}

		void update_tiles()
		{
			const auto render_window_tile_x = uint32_t(render_window_x) / tile_width;
			const auto render_window_tile_y = uint32_t(render_window_y) / tile_height;
			const uint32_t start_index = render_window_tile_x + render_window_tile_y * width;

			std::vector<float> uvs;
			for (uint32_t i = 0; i < render_window_width; ++i)
			{
				for (uint32_t j = 0; j < render_window_height; ++j)
				{
					const uint32_t index = start_index + j * width + i;
					if(index > tiles.size() - 1)
					{
						continue;
					}
					const auto& tile = tiles[index];
					const uint32_t id = tile.displayed_id;

					if (id != 0)
					{
						const TexturePatch patch = tiled_texture->get_texture_patch(id);
						uvs.push_back(patch.x1);
						uvs.push_back(patch.y1);
						uvs.push_back(patch.x2);
						uvs.push_back(patch.y1);
						uvs.push_back(patch.x2);
						uvs.push_back(patch.y2);
						uvs.push_back(patch.x1);
						uvs.push_back(patch.y2);
					}
					else
					{
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
						uvs.push_back(0);
					}
				}
			}
			vertex_array->bind();
			vertex_buffer_uvs->update(uvs.data(), sizeof(float) * uvs.size());
		}

		void draw(SceneRenderer& renderer, Shader* shader) const
		{
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};
}