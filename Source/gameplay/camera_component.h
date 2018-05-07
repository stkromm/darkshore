#pragma once

#include "core/component.h"

#include "graphics/scene_manager.h"

class CameraComponent : public Component
{
	std::shared_ptr<graphics::Camera> camera;
public:
	explicit CameraComponent(std::shared_ptr<graphics::Camera> camera) : camera(std::move(camera))
	{
	}

	void activate() const
	{
		graphics::SceneManager::get_scene()->set_camera(camera);
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> rigid_body_type = std::make_shared<ComponentType>(ComponentType{ "camera" });
		return rigid_body_type;
	}
};
