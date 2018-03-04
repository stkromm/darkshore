#pragma once

#include <string>
#include <omp.h>

#include "animation/animation_state_machine.h"

namespace AnimationManager
{
	static std::vector<std::shared_ptr<AnimationStateMachine>> animations = {};

	bool init() {
		return true;
	}

	void update(float delta)
	{
		for (int i = 0; i < animations.size(); ++i)
		{
			animations[i]->tick(delta);
		}
	}

	void shutdown()
	{
		animations.clear();
	}

	void add_animation(std::shared_ptr<AnimationStateMachine> animation)
	{
		animations.push_back(animation);
	}
}