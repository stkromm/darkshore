#pragma once

#include "core/types.h"
#include "core/math/vec4.h"
#include <vector>
#include "graphics/texture.h"

using namespace ds;

namespace ds {
	namespace graphics {
		struct TextureAtlasRegion {
			int32 x;
			int32 y;
			int32 width;
			int32 height;
		};
		struct TextureAtlasNode {
			uint32 x;
			uint32 y;
			uint32 z;
		};
		class TextureAtlas {
			/**
			 * Allocated nodes
			 */
			std::vector<TextureAtlasNode> nodes;
			/**
			 *  Width (in pixels) of the underlying texture
			 */
			size_t width;
			/**
			 * Height (in pixels) of the underlying texture
			 */
			size_t height;
			/**
			 * Depth (in bytes) of the underlying texture
			 */
			size_t depth;
			/**
			 * Allocated surface size
			 */
			size_t used;
			/**
			 * Texture identity (OpenGL)
			 */
			unsigned int id;
			/**
			 * Atlas data
			 */
			byte * data;
			std::shared_ptr<graphics::Texture> texture;

		public:
			/**
			 * Creates a new empty texture atlas.
			 *
			 * @param   width   width of the atlas
			 * @param   height  height of the atlas
			 * @param   depth   bit depth of the atlas
			 * @return          a new empty texture atlas.
			 *
			 */
			TextureAtlas(const uint32 width,
				const uint32 height,
				const uint32 depth);

			~TextureAtlas();

			std::shared_ptr<graphics::Texture> get_texture();
			/**
			 *  Allocate a new region in the atlas.
			 *
			 *  @param width  width of the region to allocate
			 *  @param height height of the region to allocate
			 *  @return       Coordinates of the allocated region
			 *
			 */
			TextureAtlasRegion get_region(
				const uint32 width,
				const uint32 height);


			/**
			 *  Upload data to the specified atlas region.
			 *
			 *  @param x      x coordinate the region
			 *  @param y      y coordinate the region
			 *  @param width  width of the region
			 *  @param height height of the region
			 *  @param data   data to be uploaded into the specified region
			 *  @param stride stride of the data
			 *
			 */
			void set_region(
				TextureAtlasRegion region,
				const unsigned char *data,
				const uint32 stride);

			void clear();
		};
	}
}