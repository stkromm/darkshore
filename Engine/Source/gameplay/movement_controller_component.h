#pragma once

#include "game/component.h"

class MovementControllerComponent : public Component
{
public:
	MovementControllerComponent() = default;

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
