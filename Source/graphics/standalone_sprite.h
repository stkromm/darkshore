#pragma once

#include "core/math/vec2.h"
#include "graphics/scene.h"
#include "graphics/texture.h"
#include "core/transform.h"
#include "graphics/sprite_vertex.h"
#include "sprite.h"

namespace graphics
{
	class StandaloneSprite : public Sprite
	{
	private:
		Vertex vertices[4]{};

		uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<Shader> shader;
		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
	public:
		StandaloneSprite(std::shared_ptr<Transform> transform, math::FVec2 offset, math::FVec2 size, TexturePatch& patch,
			uint32_t color = 0x00000000);
		~StandaloneSprite();

		std::shared_ptr<Texture> get_texture() const 
		{
			return texture;
		}

		void change_patch(TexturePatch& patch);

		void draw(float interpolation) const override;
	};
}
