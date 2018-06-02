#pragma once

#include "game/component.h"
#include "animation/animation_manager.h"
#include "game/component_type.h"
namespace ds
{

	class AnimationComponent : public game::Component
	{
		std::shared_ptr<AnimationStateMachine> animation;
	public:
		explicit AnimationComponent(const std::shared_ptr<AnimationStateMachine> animation) : animation(animation)
		{
			AnimationManager::add_animation(animation);
		}

		static std::shared_ptr<game::ComponentType> get_type()
		{
			static std::shared_ptr<game::ComponentType> rigid_body_type = std::make_shared<game::ComponentType>(game::ComponentType{
				"sprite_animation"
				});
			return rigid_body_type;
		}

		std::shared_ptr<AnimationStateMachine> get_animation() const
		{
			return animation;
		}
	};

}