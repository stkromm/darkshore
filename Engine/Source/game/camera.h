#pragma once

#include <iostream>

#include "core/transform.h"
#include "platform/window_manager.h"
#include "core/logger/log.h"

namespace ds {
	namespace scene
	{
		struct Bounds {
			int32 x1, y1, x2, y2;
		};
		class Camera
		{
		private:
			Mat4x4 projection = Mat4x4(1);
			std::unique_ptr<Bounds> bounds;
			std::shared_ptr<Transform> transform;
			float zoom = 1.0f;
		public:
			Camera()
			{
				transform = std::make_shared<Transform>();
				transform->scale(zoom);
				calculate_projection();
			}

			~Camera()
			{
				LOG_INFO << "Delete camera" << LOG_END;
			}

			Mat4x4 get_projection() const
			{
				if (bounds) {
					transform->set_position({ 0,0 });
					auto local_to_world = transform->get_local_to_world();
					if (local_to_world.data()[3 * 4] < this->bounds->x1) {
						transform->set_position({ this->bounds->x1 - local_to_world.data()[3 * 4], transform->get_position().y });
					} else if (local_to_world.data()[3 * 4] > this->bounds->x2) {
						transform->set_position({ this->bounds->x2 - local_to_world.data()[3 * 4], transform->get_position().y });
					}
					if (local_to_world.data()[3 * 4 + 1] < this->bounds->y1) {
						transform->set_position({ transform->get_position().x, this->bounds->y1 - local_to_world.data()[3 * 4 + 1] });
					} else if (local_to_world.data()[3 * 4 + 1] > this->bounds->y2) {
						transform->set_position({ transform->get_position().x, this->bounds->y2 - local_to_world.data()[3 * 4 + 1] });
					}
				}
				return transform->get_world_to_local() * projection;
			}

			void set_bounds(int32 x1, int32 y1, int32 x2, int32 y2) {
				Bounds new_bounds = { x1,y1,x2,y2 };
				this->bounds = std::make_unique<Bounds>(new_bounds);
			}

			void remove_bounds() {
				this->bounds.release();
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
				projection = Mat4x4(1).orthographic(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -1, 1);
			}
		};
	}
}