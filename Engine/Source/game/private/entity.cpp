#include "game/entity.h"
#include "game/object.h"
#include "game/component_type.h"

Entity::Entity()
{
	transform = std::make_shared<Transform>();
}

Entity::~Entity() = default;

void Entity::self_tick()
{
	GameObject::self_tick();
	transform->update();
}

void Entity::remove_component(const std::shared_ptr<ComponentType> component)
{
	if (component)
	{
		if (components[component])
		{
			components[component]->detach();
			components.erase(component);
		}
	}
}
