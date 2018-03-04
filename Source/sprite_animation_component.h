#pragma once

#include "component.h"
#include "animation/animation_state_machine.h"
#include "animation_manager.h"

class SpriteAnimationComponent : public Component
{
	std::shared_ptr<AnimationStateMachine> animation;
public:
	SpriteAnimationComponent(std::shared_ptr<AnimationStateMachine> animation) : animation(animation)
	{
		AnimationManager::add_animation(animation);
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> rigid_body_type = std::make_shared<ComponentType>(ComponentType{ "sprite_animation" });
		return rigid_body_type;
	}
};