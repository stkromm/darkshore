#pragma once
#include "core/types.h"

namespace ds {
	namespace graphics {
		class Framebuffer
		{
			uint32 textureId;
			uint32 rboId;
			uint32 id;
			bool used;
		public:
			Framebuffer(uint32 width, uint32 height);
			~Framebuffer();

			void resize(uint32 width, uint32 height);
			void bind() const;
			void unbind() const;
			void clear();
			void render();

			bool is_complete() const;
			bool is_used() const
			{
				return used;
			}
		};
	}
}