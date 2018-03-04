#pragma once

#include "math/mat4x4.h"
#include "transform.h"

namespace graphics {
	class Renderer;

	class Renderable {
	
	public:

		virtual void draw(const float interpolation, Renderer& renderer) const {

		}
	};
}