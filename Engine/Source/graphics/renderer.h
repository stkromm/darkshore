#pragma once

#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"

namespace ds {
	namespace graphics
	{
		class SceneRenderer
		{
		private:
			//std::shared_ptr<Framebuffer> framebuffer;
		public:
			mutable uint32_t draw_calls;

			SceneRenderer();
			~SceneRenderer()
			{
				LOG_INFO << "Delete renderer" << LOG_END;
			}

			void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;
			void prepare() const;
		};
	}
}
