#pragma once

#include "core/math/vec2.h"
#include "graphics/scene.h"
#include "graphics/texture.h"
#include "core/transform.h"

namespace graphics
{
	class Sprite : public Renderable
	{
	protected:
		TexturePatch patch;
		std::shared_ptr<Transform> transform;
		math::FVec2 extends;
		uint32_t color;
		std::shared_ptr<Texture> texture;

	public:
		Sprite(std::shared_ptr<Transform> transform, math::FVec2 offset, math::FVec2 size, TexturePatch& patch,
		       uint32_t color = 0x00000000);
		~Sprite();

		std::shared_ptr<Texture> get_texture() const
		{
			return texture;
		}

		void change_patch(TexturePatch& patch);

		void draw(float interpolation) const override;

		uint32_t get_color() const
		{
			return color;
		}
		TexturePatch get_texture_patch() const
		{
			return patch;
		}
		math::FVec2 get_position() const
		{
			return { 0.f,0.f };
		};
		math::FVec2 get_extends() const
		{
			return extends;
		};
		std::shared_ptr<Transform> get_transform() const
		{
			return transform;
		}
	};
}
