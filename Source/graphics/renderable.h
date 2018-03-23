#pragma once

namespace graphics
{
	class Renderer;

	class Renderable
	{
	public:
		virtual ~Renderable() = default;

		virtual void draw(const float interpolation, Renderer& renderer) const
		{
		}
	};
}
