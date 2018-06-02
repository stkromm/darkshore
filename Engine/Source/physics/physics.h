#pragma once

#include <memory>

#include "physics/rigid_body.h"

namespace ds {
	namespace physics {
		bool init();

		void shutdown();

		void add_rigid_body(std::shared_ptr<RigidBody> rigid_body);

		void tick(float delta);
	}
}