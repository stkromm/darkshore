#include "component.h"

Component::Component(): owner(nullptr)
{
}

Component::~Component()
= default;


void Component::attach(Entity* entity)
{
	owner = entity;
	on_attach();
}

void Component::detach()
{
	owner = nullptr;
}
