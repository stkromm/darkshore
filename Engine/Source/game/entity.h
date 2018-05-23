#pragma once
#include <unordered_map>
#include <memory>

#include "game/object.h"
#include "core/transform.h"
#include "game/component.h"
#include "game/component_type.h"


class Entity : public GameObject
{
protected:
	std::shared_ptr<Transform> transform;
	std::unordered_map<std::shared_ptr<ComponentType>, std::shared_ptr<Component>> components;

public:
	Entity();
	~Entity();

	void self_tick() override;

	template <class C, class... _Types>
	void add_component(_Types&&... Args)
	{
		std::shared_ptr<C> component = std::make_shared<C>(std::forward<_Types>(Args)...);
		remove_component(C::get_type());
		components[C::get_type()] = component;
		component->attach(this);
	}

	template <class C>
	std::shared_ptr<C> get_component() const
	{
		std::shared_ptr<C> component = std::reinterpret_pointer_cast<C>(components.find(C::get_type())->second);
		return component;
	}

	void remove_component(std::shared_ptr<ComponentType> component);
};
