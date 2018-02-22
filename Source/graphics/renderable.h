#pragma once

#include "transform.h"

namespace graphics {
	class Scene;
	class Renderer;

	class Renderable {
	protected:
		Scene* scene;
	public:
		void set_scene(Scene* scene)
		{
			this->scene = scene;
		}

		const Scene* get_scene() {
			return scene;
		}

		Transform get_world_transform() {}
		virtual void draw(Renderer& renderer) const {

		}
	};
}