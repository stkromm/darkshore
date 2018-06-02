#pragma once

#include "game/component.h"

namespace ds {
	class MovementControllerComponent : public game::Component
	{
	public:
		MovementControllerComponent() = default;

		static std::shared_ptr<game::ComponentType> get_type()
		{
			static std::shared_ptr<game::ComponentType> sprite_type = std::make_shared<game::ComponentType>(game::ComponentType{
				"movement-controller"
				});
			return sprite_type;
		}

		void on_attach() override
		{
		}

	};
}