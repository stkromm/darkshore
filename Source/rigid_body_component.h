#pragma once

#include "component.h"
#include "physics/physics.h"


class RigidBodyComponent : public Component
{
	std::shared_ptr<physics::RigidBody> animation;
public:
	RigidBodyComponent(std::shared_ptr<physics::RigidBody> rigid_body) : animation(rigid_body)
	{
		physics::PhysicSimulation::add_rigid_body(rigid_body);
	}

	std::shared_ptr<physics::RigidBody> get_rigid_body()
	{
		return animation;
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> rigid_body_type = std::make_shared<ComponentType>(ComponentType{ "rigid_body" });
		return rigid_body_type;
	}
};
