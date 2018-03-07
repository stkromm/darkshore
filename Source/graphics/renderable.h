#pragma once

#include "core/math/mat4x4.h"
#include "core/transform.h"

namespace graphics {
	class Renderer;

	class Renderable {
	
	public:

		virtual void draw(const float interpolation, Renderer& renderer) const {

		}
	};
}