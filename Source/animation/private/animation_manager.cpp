#include "animation/animation_manager.h"

namespace AnimationManager
{
	static std::vector<std::shared_ptr<AnimationStateMachine>> animations = {};

	bool init()
	{
		return true;
	}

	void update(const float delta)
	{
		for (auto& animation : animations)
		{
			animation->tick(delta);
		}
	}

	void shutdown()
	{
		animations.clear();
	}

	void add_animation(const std::shared_ptr<AnimationStateMachine> animation)
	{
		animations.push_back(animation);
	}

	void remove_animation(const std::shared_ptr<AnimationStateMachine>& animation)
	{
		//
	}
}
