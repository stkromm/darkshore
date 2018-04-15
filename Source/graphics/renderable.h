#pragma once

namespace graphics
{
	class Renderable
	{
	public:
		virtual ~Renderable() = default;

		virtual void draw(const float interpolation) const
		{
		}
	};
}
