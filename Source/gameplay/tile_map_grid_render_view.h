#pragma once

#include <vector>

#include "core/math/vine_math.h"

#include "graphics/scene_renderer.h"
#include "graphics/render_manager.h"
#include "graphics/texture.h"
#include "graphics/tiled_texture.h"

#include "tile_grid.h"

namespace tilemap
{
	class TileMapGridRenderView
	{
		uint32_t render_window_width = 42;
		uint32_t render_window_height = 25;
		float render_window_x = 0;
		float render_window_y = 0;

		int prev_render_window_tile_x = 0;
		int prev_render_window_tile_y = 0;

		std::unique_ptr<graphics::VertexBuffer> vertex_buffer_position;
		std::unique_ptr<graphics::VertexBuffer> vertex_buffer_uvs;
		std::unique_ptr<graphics::VertexBuffer> vertex_buffer_color;
		std::unique_ptr<graphics::VertexArray> vertex_array;
		std::unique_ptr<graphics::IndexBuffer> index_buffer;
		std::shared_ptr<graphics::TiledTexture> tiled_texture;
		std::shared_ptr<graphics::Shader> shader;
		std::shared_ptr<TileGrid> layer;
		std::vector<float> uvs;

	public:
		TileMapGridRenderView(std::shared_ptr<TileGrid> layer,
			std::shared_ptr<graphics::TiledTexture>& tiled_texture);

		~TileMapGridRenderView();

		void set_render_window_size(uint32_t x, uint32_t y);

		void update_render_window(float x, float y);

		void draw(graphics::Shader* shader) const;

		void update();

	private:
		void update_grid();
		void update_tiles();
	};
}
