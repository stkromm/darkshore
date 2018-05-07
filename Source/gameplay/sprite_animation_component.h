#pragma once

#include "core/component.h"
#include "animation/animation_manager.h"
#include "core/component_type.h"

class AnimationComponent : public Component
{
	std::shared_ptr<AnimationStateMachine> animation;
public:
	explicit AnimationComponent(const std::shared_ptr<AnimationStateMachine> animation) : animation(animation)
	{
		AnimationManager::add_animation(animation);
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> rigid_body_type = std::make_shared<ComponentType>(ComponentType{
			"sprite_animation"
		});
		return rigid_body_type;
	}

	std::shared_ptr<AnimationStateMachine> get_animation() const
	{
		return animation;
	}
};
