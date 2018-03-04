#pragma once

#include "animation/animation_state_machine.h"

namespace AnimationManager
{
	bool init();

	void update(const float delta);

	void shutdown();

	void add_animation(std::shared_ptr<AnimationStateMachine> animation);
}