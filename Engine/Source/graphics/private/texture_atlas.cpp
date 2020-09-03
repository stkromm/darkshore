/*
 * Based on Freetype GL - A C OpenGL Freetype engine
 *
 * Distributed under the OSI-approved BSD 2-Clause License.  See accompanying
 * file `LICENSE` for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits>
#include "core/logger/log.h"
#include "graphics/texture_atlas.h"

ds::graphics::TextureAtlas::TextureAtlas(const uint32 width,
	const uint32 height,
	const uint32 depth) : width(width), height(height), depth(depth)
{
	this->used = 0;
	this->id = 0;

	// We want a one pixel border around the whole atlas to avoid any artefact when
	// sampling texture
	this->nodes.push_back({ 1,1,width - 2 });
	this->data = (unsigned char *) calloc(width*height*depth, sizeof(unsigned char));
	this->texture = std::make_shared<graphics::Texture>(this->width, this->height, this->data);
}

ds::graphics::TextureAtlas::~TextureAtlas()
{
}

void ds::graphics::TextureAtlas::set_region(ds::graphics::TextureAtlasRegion region, const unsigned char * data, const uint32 stride)
{
	size_t i;
	size_t depth = this->depth;
	size_t charsize;

	assert(region.x > 0);
	assert(region.y > 0);
	assert(region.x < (this->width - 1));
	assert((region.x + region.width) <= (this->width - 1));
	assert(region.y < (this->height - 1));
	assert((region.y + region.height) <= (this->height - 1));

	//prevent copying data from undefined position 
	//and prevent memcpy's undefined behavior when count is zero
	assert(region.height == 0 || (data != NULL && region.width > 0));


	charsize = sizeof(char);
	for (i = 0; i < region.height; ++i)
	{
		memcpy(this->data + ((region.y + i)*this->width + region.x) * charsize * this->depth,
			data + (i * region.width * 4), region.width * charsize * this->depth);
	}
	/*
	LOG_INFO << "Texture Atlas" << LOG_END;
	for (int a = 0; a < width; ++a)
	{
		for (int b = 0; b < height; ++b)
		{
			LOG_INFO << (reinterpret_cast<int*>(this->data))[a * width + b];
		}
		LOG_INFO << LOG_END;
	}
	*/
	this->texture->update_data(this->data);
}

std::shared_ptr<ds::graphics::Texture> ds::graphics::TextureAtlas::get_texture() {
	return this->texture;
}

// TODO Should be moved to class scope.
int32 x = 1;
int32 maxRowHeight = 0;
int32 y = 1;
ds::graphics::TextureAtlasRegion ds::graphics::TextureAtlas::get_region(
	const uint32 width,
	const uint32 height)
{
	if (x + width >= this->width - 2) {
		y += maxRowHeight;
		x = 1;
		maxRowHeight = height;
		return {
			x, y,
			static_cast<int32>(width),
			static_cast<int32>(height)
		};
	} else {
		x += width;
		maxRowHeight = maxRowHeight > height ? maxRowHeight : height;
		return {
			x - static_cast<int32>(width),
			y,
			static_cast<int32>(width),
			static_cast<int32>(height)
		};
	}
}

void ds::graphics::TextureAtlas::clear()
{
	assert(this->data);
	this->nodes.clear();
	x = 0;
	y = 0;
	memset(this->data, 0, this->width*this->height*this->depth);
}