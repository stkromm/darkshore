#pragma once

#include "core/component.h"
#include "graphics/sprite.h"


class SpriteComponent : public Component
{
	std::shared_ptr<graphics::Sprite> sprite;
public:
	explicit SpriteComponent(const std::shared_ptr<graphics::Sprite> sprite) : sprite(sprite)
	{
		graphics::SceneManager::get_scene()->add_renderable(sprite);
	}

	static std::shared_ptr<ComponentType> get_type()
	{
		static std::shared_ptr<ComponentType> sprite_type = std::make_shared<ComponentType>(ComponentType{"sprite"});
		return sprite_type;
	}

	std::shared_ptr<graphics::Sprite> get_sprite() const
	{
		return sprite;
	}
};
