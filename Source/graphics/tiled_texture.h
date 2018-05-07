#pragma once

#include <memory>
#include "graphics/texture.h"

namespace graphics
{
	struct VerticalTileStrip
	{
		const std::shared_ptr<Texture> texture;
		const float x = 0;
		const float tile_width = 0;
		const float tile_height = 0;
		const float offset_start_y = 0;
		const uint32_t size_y = 0;

		TexturePatch operator[](const uint32_t y) const
		{
			return
			{
				texture,
				x,
				(size_y - 1 - y) * tile_height + offset_start_y,
				x + tile_width,
				(size_y - 1 - y) * tile_height + offset_start_y + tile_height
			};
		}
	};

	class TiledTexture
	{
	private:
		const std::shared_ptr<Texture> texture;
		const uint32_t tile_width;
		const uint32_t tile_height;

		const uint32_t offset_start_x;
		const uint32_t offset_start_y;

		const uint32_t size_x;
		const uint32_t size_y;

	public:
		TiledTexture(const std::shared_ptr<Texture> texture,
		             const uint32_t tile_width, const uint32_t tile_height,
		             const uint32_t offset_start_x = 0, const uint32_t offset_start_y = 0,
		             const uint32_t offset_end_x = 0, const uint32_t offset_end_y = 0) :
			texture(texture),
			tile_width(tile_width),
			tile_height(tile_height),
			offset_start_x(offset_start_x),
			offset_start_y(offset_start_y),
			size_x((texture->get_width() - offset_start_x - offset_end_x) / tile_width),
			size_y((texture->get_height() - offset_start_y - offset_end_y) / tile_height)
		{
		}

		~TiledTexture() = default;

		VerticalTileStrip operator[](const uint32_t x) const
		{
			return
			{
				texture,
				(x * tile_width + offset_start_x) / (float(size_x) * tile_width),
				tile_width / (float(size_x) * tile_width),
				tile_height / (float(size_y) * tile_height),
				offset_start_y / (float(size_y) * tile_height),
				get_y_count()
			};
		}

		uint32_t get_tile_width() const
		{
			return tile_width;
		}

		uint32_t get_tile_height() const
		{
			return tile_height;
		}

		uint32_t get_y_count() const
		{
			return size_y;
		}

		uint32_t get_x_count() const
		{
			return size_x;
		}

		std::shared_ptr<Texture> get_texture() const
		{
			return texture;
		}

		TexturePatch get_texture_patch(const int index) const
		{
			return (*this)[index % size_x][index / size_x];
		}
	};
}
