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

namespace graphics {
	struct TileMapSpriteLayer {
		uint32_t width;
		uint32_t height;

		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;

		TileMapSpriteLayer(uint32_t size_x, uint32_t size_y, uint32_t tile_width, uint32_t tile_height, tmx::TileLayer* layer, std::shared_ptr<TiledTexture>& tiled_texture, uint32_t columns)
		{
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;

			uint32_t drawn_tiles = 0;

			for (uint32_t i = 0; i < size_x; ++i)
			{
				for (uint32_t j = 0; j < size_y; ++j)
				{
					uint32_t index = j * size_x + i;
					if (layer->getTiles()[index].ID != 0)
					{
						indices.push_back(drawn_tiles * 4 + 0);
						indices.push_back(drawn_tiles * 4 + 1);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 2);
						indices.push_back(drawn_tiles * 4 + 3);
						indices.push_back(drawn_tiles * 4 + 0);

						uint32_t color = 0x000000FF;
						float x = (float)(tile_width * i);
						float y = (float)(tile_height * (size_y - j));

						uint32_t id = layer->getTiles()[index].ID - 1;

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
			vb_layout.push<uint32_t>(1);

			vertex_array->add_buffer(*vertex_buffer, vb_layout);
		}

		~TileMapSpriteLayer()
		{
			std::cout << "Delete layer" << std::endl;
		}

		void draw(Renderer& renderer, Shader* shader) const
		{
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};
};