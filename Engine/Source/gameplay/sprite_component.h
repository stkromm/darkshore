#pragma once

#include "game/component.h"
#include "scene/sprite.h"
#include "scene/scene_manager.h"

namespace ds {
	class SpriteComponent : public game::Component
	{
		std::shared_ptr<scene::Sprite> sprite;

	public:
		explicit SpriteComponent(const std::shared_ptr<scene::Sprite> sprite) : sprite(sprite)
		{
			scene::SceneManager::get_scene()->add_renderable(sprite);
		}

		static std::shared_ptr<game::ComponentType> get_type()
		{
			static std::shared_ptr<game::ComponentType> sprite_type = std::make_shared<game::ComponentType>(game::ComponentType{ "sprite" });
			return sprite_type;
		}

		std::shared_ptr<scene::Sprite> get_sprite() const
		{
			return sprite;
		}
	};
}