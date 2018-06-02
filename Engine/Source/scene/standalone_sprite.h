#pragma once

#include "core/math/vec2.h"
#include "scene/scene.h"
#include "graphics/texture.h"
#include "core/transform.h"
#include "scene/sprite_vertex.h"
#include "sprite.h"
#include "shader_asset.h"

namespace ds {
	namespace scene
	{
		class StandaloneSprite : public Sprite
		{
		private:
			Vertex vertices[4]{};

			uint32_t indices[6] = {
				0, 1, 2,
				2, 3, 0
			};

			std::shared_ptr<ShaderAsset> shader_asset;
			std::shared_ptr<ds::graphics::Shader> shader;
			std::unique_ptr<ds::graphics::VertexBuffer> vertex_buffer;
			std::unique_ptr<ds::graphics::VertexArray> vertex_array;
			std::unique_ptr<ds::graphics::IndexBuffer> index_buffer;
		public:
			StandaloneSprite(std::shared_ptr<Transform> transform, ds::FVec2 offset, ds::FVec2 size, ds::graphics::TexturePatch& patch,
				uint32_t color = 0x00000000);
			~StandaloneSprite();

			std::shared_ptr<ds::graphics::Texture> get_texture() const
			{
				return texture;
			}

			void change_patch(ds::graphics::TexturePatch& patch);

			void draw(float interpolation) const override;
		};
	}
}