#pragma once

#include <vector>

#include "core/math/vec2.h"
#include "graphics/scene.h"
#include "graphics/texture.h"
#include "core/transform.h"
#include "platform/asset.h"
#include "platform/asset_manager.h"
#include "graphics/sprite_vertex.h"

namespace graphics {

	class Sprite : public Renderable
	{
	private:
		Vertex vertices[4];

		uint32_t indices[6] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<Transform> transform;
		math::Vec2 extends;

		std::shared_ptr<graphics::Texture> texture;
		graphics::TexturePatch& patch;

		std::shared_ptr<Shader> shader;
		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
	public:
		Sprite(std::shared_ptr<Transform> transform, math::Vec2 offset, math::Vec2 size, graphics::TexturePatch& patch, uint32_t color = 0x00000000);
		~Sprite();
		std::shared_ptr<Texture> get_texture()
		{
			return texture;
		}
		void change_patch(TexturePatch& patch);

		void draw(const float interpolation, Renderer& renderer) const override;
	};
}

