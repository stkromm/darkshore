#include "tilemap/tile_layer.h"
#include "core/platform/window_manager.h"
#include "core/logger/log.h"

/*
tilemap::TileLayer::TileLayer(const uint32_t size_x, const uint32_t size_y,
	const uint32_t tile_width, const uint32_t tile_height,
	std::shared_ptr<graphics::TiledTexture>& tiled_texture)
{
	std::vector<Tile> tiles;
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
	/*
	grid = std::make_shared<TileGrid>(
		size_x, size_y,
		tile_width, tile_height,
		std::move(tiles)
		);

	render_view = std::make_shared<TileMapGridRenderView>(grid, tiled_texture);

	render_view->set_render_window_size(platform::WindowManager::get_window().get_screen().width, platform::WindowManager::get_window().get_screen().height);
	platform::WindowManager::get_window().add_resize_callback([this](uint32_t width, uint32_t height)
	{
		render_view->set_render_window_size(width, height);
	});
}
*/
tilemap::TileLayer::~TileLayer()
{
	LOG_INFO << "Delete layer" << LOG_END;
}

void tilemap::TileLayer::parse(json layer_source)
{
	const int32 x = layer_source["x"];
	const int32 y = layer_source["y"];
	const uint32 height = layer_source["height"];
	this->height = height;
	const uint32 width = layer_source["width"];
	this->width = width;
	float opacity = layer_source["opacity"];

	std::vector<uint32> tiles;
	tiles.resize(height * width);

	for(auto& id : layer_source["data"])
	{
		tiles.push_back(id);
	}
}

void tilemap::TileLayer::update_tile_state(const uint32_t o_id, const uint32_t d_id)
{
	tile_states[o_id] = d_id;
}
