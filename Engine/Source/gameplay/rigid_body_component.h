#pragma once

#include "game/component.h"
#include "physics/physics.h"

namespace ds {
	class RigidBodyComponent : public game::Component
	{
		std::shared_ptr<physics::RigidBody> animation;
	public:
		explicit RigidBodyComponent(const std::shared_ptr<physics::RigidBody> rigid_body) : animation(rigid_body)
		{
			add_rigid_body(rigid_body);
		}

		std::shared_ptr<physics::RigidBody> get_rigid_body() const
		{
			return animation;
		}

		static std::shared_ptr<game::ComponentType> get_type()
		{
			static std::shared_ptr<game::ComponentType> rigid_body_type = std::make_shared<game::ComponentType>(game::ComponentType{ "rigid_body" });
			return rigid_body_type;
		}
	};
}