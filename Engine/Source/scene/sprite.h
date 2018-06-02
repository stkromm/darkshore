#pragma once

#include "core/math/vec2.h"
#include "scene/scene.h"
#include "graphics/texture.h"
#include "core/transform.h"
#include "renderable.h"

namespace ds {
namespace scene
{
	class Sprite : public Renderable
	{
	protected:
		ds::graphics::TexturePatch patch;
		std::shared_ptr<Transform> transform;
		ds::FVec2 extends;
		uint32_t color;
		std::shared_ptr<ds::graphics::Texture> texture;

	public:
		Sprite(std::shared_ptr<Transform> transform, ds::FVec2 offset, ds::FVec2 size, ds::graphics::TexturePatch& patch,
			uint32_t color = 0x00000000);

		~Sprite();

		std::shared_ptr<ds::graphics::Texture> get_texture() const
		{
			return texture;
		}

		void change_patch(ds::graphics::TexturePatch& patch);

		void draw(float interpolation) const override;

		uint32_t get_color() const
		{
			return color;
		}

		ds::graphics::TexturePatch get_texture_patch() const
		{
			return patch;
		}

		ds::FVec2 get_position() const
		{
			return transform->get_position();
		};

		ds::FVec2 get_extends() const
		{
			return extends;
		};

		std::shared_ptr<Transform> get_transform() const
		{
			return transform;
		}
	};
}
}