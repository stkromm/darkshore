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

#include "graphics/texture_atlas.h"

ds::graphics::TextureAtlas::TextureAtlas(const size_t width,
	const size_t height,
	const size_t depth) : width(width), height(height), depth(depth)
{
	this->used = 0;
	this->id = 0;

	// We want a one pixel border around the whole atlas to avoid any artefact when
	// sampling texture
	this->nodes.push_back({ 1,1,width - 2 });
	this->data = (unsigned char *)calloc(width*height*depth, sizeof(unsigned char));
}

ds::graphics::TextureAtlas::~TextureAtlas()
{
}

void ds::graphics::TextureAtlas::set_region(
	ds::graphics::TextureAtlasRegion region,
	const unsigned char * data,
	const size_t stride)
{
	size_t i;
	size_t depth;
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

	depth = this->depth;
	charsize = sizeof(char);
	for (i = 0; i < region.height; ++i)
	{
		memcpy(this->data + ((region.y + i)*this->width + region.x) * charsize * depth,
			data + (i*stride) * charsize, region.width * charsize * depth);
	}
}


int ds::graphics::TextureAtlas::fit(
	const size_t index,
	const size_t width,
	const size_t height)
{
	auto node = this->nodes[index];
	auto x = node.x;
	auto y = node.y;
	auto width_left = width;
	auto i = index;

	if ((x + width) > (this->width - 1))
	{
		return -1;
	}
	y = node.y;
	while (width_left > 0)
	{
		node = this->nodes[i];
		if (node.y > y)
		{
			y = node.y;
		}
		if ((y + height) > (this->height - 1))
		{
			return -1;
		}
		width_left -= node.z;
		++i;
	}
	return y;
}


void ds::graphics::TextureAtlas::merge()
{
	for (uint32 i = 0; i < this->nodes.size() - 1; ++i)
	{
		auto node = this->nodes[i];
		auto next = this->nodes[i + 1];
		if (node.y == next.y)
		{
			node.z += next.z;
			this->nodes.erase(this->nodes.begin() + i + 1);
			--i;
		}
	}
}

ds::graphics::TextureAtlasRegion ds::graphics::TextureAtlas::get_region(
	const size_t width,
	const size_t height)
{
	int y, best_index;
	size_t best_height, best_width;
	ds::graphics::TextureAtlasNode node, prev;
	ds::graphics::TextureAtlasRegion region = { 0,0,width,height };
	size_t i;

	best_height = std::numeric_limits<uint32>::max();
	best_index = -1;
	best_width = std::numeric_limits<uint32>::max();
	for (i = 0; i < this->nodes.size(); ++i)
	{
		y = this->fit(i, width, height);
		if (y >= 0)
		{
			node = this->nodes[i];
			if (((y + height) < best_height) ||
				(((y + height) == best_height) && (node.z > 0 && (size_t)node.z < best_width)))
			{
				best_height = y + height;
				best_index = i;
				best_width = node.z;
				region.x = node.x;
				region.y = y;
			}
		}
	}

	if (best_index == -1)
	{
		region = { -1, -1, 0, 0 };
		return region;
	}

	node = ds::graphics::TextureAtlasNode();
	node.x = region.x;
	node.y = region.y + height;
	node.z = width;
	this->nodes.insert(this->nodes.begin() + best_index, node);

	for (i = best_index + 1; i < this->nodes.size(); ++i)
	{
		node = this->nodes[i];
		prev = this->nodes[i - 1];

		if (node.x < (prev.x + prev.z))
		{
			int shrink = prev.x + prev.z - node.x;
			node.x += shrink;
			node.z -= shrink;
			if (node.z <= 0)
			{
				this->nodes.erase(this->nodes.begin() + i);
				--i;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	this->merge();
	this->used += width * height;
	return region;
}

void ds::graphics::TextureAtlas::clear()
{
	assert(this->data);
	this->nodes.clear();
	this->used = 0;
	// We want a one pixel border around the whole atlas to avoid any artefact when
	// sampling texture
	this->nodes.push_back({ 1,1,this->width - 2 });
	memset(this->data, 0, this->width*this->height*this->depth);
}