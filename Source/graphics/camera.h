#pragma once

#include <iostream>

#include "core/transform.h"
#include "platform/window_manager.h"

namespace graphics
{
	class Camera
	{
	private:
		math::Mat4x4 projection = math::Mat4x4(1);
		std::shared_ptr<Transform> transform;
		float zoom = 1.25f;
	public:
		Camera()
		{
			transform = std::make_shared<Transform>();
			transform->scale(zoom);
			calculate_projection();
		}

		~Camera()
		{
			std::cout << "Delete camera" << std::endl;
		}

		math::Mat4x4 get_projection() const
		{
			return transform->get_world_to_local() * projection;
		}

		void set_zoom(const float zoom)
		{
			this->zoom = zoom;
			transform->set_scale(zoom);
		}

		float get_zoom() const
		{
			return zoom;
		}

		std::shared_ptr<Transform> get_transform() const
		{
			return transform;
		}
	private:
		void calculate_projection() 
		{
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			const float aspect = float(screen.height) / screen.width;
			const float width = 1920;
			const float height = 1920 * aspect;
			projection = math::Mat4x4(1).orthographic(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -1, 1);
		}
	};
}