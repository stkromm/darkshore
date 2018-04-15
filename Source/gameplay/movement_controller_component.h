#pragma once

#include "platform/window.h"
#include "gameplay/rigid_body_component.h"
#include "core/component.h"
#include "core/entity.h"

class MovementControllerComponent : public Component
{
public:
	MovementControllerComponent()
	{
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> sprite_type = std::make_shared<ComponentType>(ComponentType{
			"movement-controller"
		});
		return sprite_type;
	}

	void on_attach() override
	{
	}

};
