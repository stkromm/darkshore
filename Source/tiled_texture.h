#pragma once

#include <memory>
#include "graphics\texture.h"

namespace graphics
{
	struct VerticalTileStrip
	{
		const std::shared_ptr<Texture> texture;
		const float x;
		const float tile_width;
		const float tile_height;
		const float offset_start_y;
		const unsigned int size_y;

		TexturePatch operator[](const unsigned int y) const
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
		const unsigned int tile_width;
		const unsigned int tile_height;

		const unsigned int offset_start_x;
		const unsigned int offset_start_y;

		const unsigned int size_x;
		const unsigned int size_y;

	public:
		TiledTexture(const std::shared_ptr<Texture> texture,
			const unsigned int tile_width, const unsigned int tile_height,
			const unsigned int offset_start_x = 0, const unsigned int offset_start_y = 0,
			const unsigned int offset_end_x = 0, const unsigned int offset_end_y = 0) :
			texture(texture),
			tile_width(tile_width),
			tile_height(tile_height),
			size_x((texture->get_width() - offset_start_x - offset_end_x) / tile_width),
			size_y((texture->get_height() - offset_start_y - offset_end_y) / tile_height),
			offset_start_x(offset_start_x),
			offset_start_y(offset_start_y)
		{
		}

		~TiledTexture()
		{

		}

		VerticalTileStrip operator[](const unsigned int x) const
		{
			ASSERT(x < size_x);
			return
			{
				texture,
				(x * tile_width + offset_start_x) / ((float)size_x * tile_width),
				tile_width / ((float)size_x * tile_width),
				tile_height / ((float)size_y * tile_height),
				offset_start_y / ((float)size_y * tile_height),
				get_y_count()
			};
		}

		unsigned int get_tile_width() const
		{
			return tile_width;
		}

		unsigned int get_tile_height() const
		{
			return tile_height;
		}
		unsigned int get_y_count() const
		{
			return size_y;
		}

		unsigned int get_x_count() const
		{
			return size_x;
		}

		std::shared_ptr<Texture> get_texture() const
		{
			return texture;
		}

		TexturePatch get_texture_patch(int index) const
		{
			return (*this)[index % size_x][index / size_x];
		}
	};
}

