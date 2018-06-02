#pragma once

#include <game/camera.h>
#include "scene/scene_manager.h"

namespace ds {
	class CameraComponent : public game::Component
	{
		std::shared_ptr<scene::Camera> camera;
	public:
		explicit CameraComponent(std::shared_ptr<scene::Camera> camera) : camera(std::move(camera))
		{
		}

		void activate() const
		{
			scene::SceneManager::get_scene()->set_camera(camera);
		}

		static std::shared_ptr<game::ComponentType> get_type()
		{
			static std::shared_ptr<game::ComponentType> rigid_body_type = std::make_shared<game::ComponentType>(game::ComponentType{ "camera" });
			return rigid_body_type;
		}
	};
}