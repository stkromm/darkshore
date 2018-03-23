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
		const std::function<platform::KeyCallback> key_callback = [this
			](const size_t k, const size_t a, const size_t b, const size_t c)
		{
			this->key_press(k, a, b, c);
		};
		platform::WindowManager::get_window().add_key_callback(key_callback);
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

	void key_press(const size_t k, const size_t m, const size_t s, const size_t a) const
	{
		//std::cout << "Key press oO" << std::endl;

		Entity* owner = get_owner();
		if (k == GLFW_KEY_W)
		{
			owner->get_component<RigidBodyComponent>()->get_rigid_body()->add_impuls({0, 300});
			//transform->translate({ 0,3 });
		}
		if (k == GLFW_KEY_S)
		{
			owner->get_component<RigidBodyComponent>()->get_rigid_body()->add_impuls({0, -300});
			//transform->translate({ 0,-3 });
		}
		if (k == GLFW_KEY_A)
		{
			owner->get_component<RigidBodyComponent>()->get_rigid_body()->add_impuls({-300, 0});
			//transform->translate({ -3,0 });
		}
		if (k == GLFW_KEY_D)
		{
			owner->get_component<RigidBodyComponent>()->get_rigid_body()->add_impuls({300, 0});
			//transform->translate({ 3,0 });
		}
	}
};
