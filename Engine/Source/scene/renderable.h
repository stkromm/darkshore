#pragma once

namespace ds {
	namespace scene
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
}