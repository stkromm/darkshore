#pragma once
#include "component_type.h"

class Entity;


class Component
{
private:
	Entity * owner;

public:
	Component();
	~Component();

	Entity* get_owner() const
	{
		return owner;
	}

	bool is_attached() const
	{
		return owner != nullptr;
	}

	void attach(Entity* entity);

	virtual void on_attach() {}

	void detach();
};

