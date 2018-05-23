#include "tile_map_grid_render_view.h"

tilemap::TileMapGridRenderView::TileMapGridRenderView(std::shared_ptr<TileGrid> layer,
	std::shared_ptr<graphics::TiledTexture>& tiled_texture) : tiled_texture(tiled_texture), layer(layer)
{
	std::vector<float> positions;
	positions.reserve(8 * render_window_width * render_window_height);
	std::vector<float> uvs;
	uvs.resize(8 * render_window_width * render_window_height);
	std::vector<uint32_t> colors;
	colors.resize(4 * render_window_width * render_window_height);

	std::vector<uint32_t> indices;

	vertex_array = std::make_unique<graphics::VertexArray>();

	vertex_buffer_position = std::make_unique<graphics::VertexBuffer>(positions.data(), sizeof(float) * positions.size());
	graphics::VertexBufferLayout vb_layout_pos;
	vb_layout_pos.push<float>(2);
	vertex_array->add_buffer(*vertex_buffer_position, vb_layout_pos);

	vertex_buffer_uvs = std::make_unique<graphics::VertexBuffer>(uvs.data(), sizeof(float) * uvs.size());
	graphics::VertexBufferLayout vb_layout_uvs;
	vb_layout_uvs.push<float>(2);
	vertex_array->add_buffer(*vertex_buffer_uvs, vb_layout_uvs);

	vertex_buffer_color = std::make_unique<graphics::VertexBuffer>(colors.data(), sizeof(uint32_t) * colors.size());
	graphics::VertexBufferLayout vb_layout_col;
	vb_layout_col.push<uint32_t>(1);
	vertex_array->add_buffer(*vertex_buffer_color, vb_layout_col);

	index_buffer = std::make_unique<graphics::IndexBuffer>(indices);

	set_render_window_size(platform::WindowManager::get_window().get_screen().width, platform::WindowManager::get_window().get_screen().height);
	platform::WindowManager::get_window().add_resize_callback([this](uint32_t width, uint32_t height)
	{
		set_render_window_size(width, height);
	});
}

tilemap::TileMapGridRenderView::~TileMapGridRenderView()
{
	std::cout << "Delete layer" << std::endl;
}

void tilemap::TileMapGridRenderView::set_render_window_size(const uint32_t x, const uint32_t y)
{
	render_window_width = x / layer->tile_width * 2 + 2;
	render_window_height = y / layer->tile_height * 2 + 2;
	update_grid();
}

void tilemap::TileMapGridRenderView::update_render_window(const float x, const float y)
{
	render_window_x = x;
	render_window_y = y;

	const auto render_window_tile_x = math::clamp(uint32_t(render_window_x) / layer->tile_width, layer->width);
	const auto render_window_tile_y = math::clamp(uint32_t(render_window_y) / layer->tile_height, layer->height);

	if (abs(prev_render_window_tile_x - int(render_window_tile_x)) >= 1 || abs(prev_render_window_tile_y - int(render_window_tile_y)) >= 1)
	{
		update_tiles();
	}

	prev_render_window_tile_x = render_window_tile_x;
	prev_render_window_tile_y = render_window_tile_y;
}


void tilemap::TileMapGridRenderView::draw(graphics::Shader* shader) const
{
	graphics::RenderManager::get_scene_renderer()->draw(*vertex_array, *index_buffer, *shader);
}

void tilemap::TileMapGridRenderView::update_grid()
{
	std::vector<float> positions;
	positions.reserve(8 * render_window_width * render_window_height);
	std::vector<uint32_t> indices;
	uint32_t drawn_tiles = 0;
	for (uint32_t i = 0; i < render_window_width; ++i)
	{
		const auto x = float(layer->tile_width * i);
		for (uint32_t j = 0; j < render_window_height; ++j)
		{
			indices.push_back(drawn_tiles * 4 + 0);
			indices.push_back(drawn_tiles * 4 + 1);
			indices.push_back(drawn_tiles * 4 + 2);
			indices.push_back(drawn_tiles * 4 + 2);
			indices.push_back(drawn_tiles * 4 + 3);
			indices.push_back(drawn_tiles * 4 + 0);

			const auto y = float(layer->tile_height * (render_window_height - j));

			positions.push_back(x);
			positions.push_back(y);

			positions.push_back(x + layer->tile_width);
			positions.push_back(y);

			positions.push_back(x + layer->tile_width);
			positions.push_back(y + layer->tile_height);

			positions.push_back(x);
			positions.push_back(y + layer->tile_height);

			drawn_tiles++;
		}
	}
	vertex_buffer_position->update(positions.data(), sizeof(float) * positions.size());
	index_buffer->update(indices);
}

void tilemap::TileMapGridRenderView::update_tiles()
{
	const auto render_window_tile_x = math::clamp(uint32_t(render_window_x) / layer->tile_width, layer->width - render_window_width - 1);
	auto render_window_tile_y = math::clamp(uint32_t(render_window_y) / layer->tile_height, layer->height - render_window_height - 1);
	render_window_tile_y = math::invert(render_window_tile_y, layer->height - render_window_height);
	const uint32_t start_index = render_window_tile_x + render_window_tile_y * layer->width;

	uvs.clear();
	for (uint32_t i = 0; i < render_window_width; ++i)
	{
		for (uint32_t j = 0; j < render_window_height; ++j)
		{
			const uint32_t index = start_index + j * layer->width + i;

			const auto& tile = layer->tiles[index];
			const uint32_t id = tile.displayed_id;

			if (id != 0)
			{
				const graphics::TexturePatch patch = tiled_texture->get_texture_patch(id);
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

void tilemap::TileMapGridRenderView::update()
{
	update_tiles();
}