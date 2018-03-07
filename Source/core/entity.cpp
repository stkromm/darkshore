#include "core/entity.h"

Entity::Entity() {
	transform = std::make_shared<Transform>();
}
Entity::~Entity() {}

void Entity::self_tick()
{
	GameObject::self_tick();
	transform->update();
}

void Entity::remove_component(std::shared_ptr<ComponentType> component)
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