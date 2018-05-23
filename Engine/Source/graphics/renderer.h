#pragma once

#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"
#include "framebuffer.h"
#include <memory>

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

			void draw(const ds::graphics::VertexArray& vertex_array, const ds::graphics::IndexBuffer& index_buffer, const ds::graphics::Shader& shader) const;
			void prepare() const;
		};
	}
}
