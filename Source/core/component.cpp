#include "component.h"

Component::Component()
{
}

Component::~Component()
{
}


void Component::attach(Entity* entity)
{
	owner = entity;
	on_attach();
}

void Component::detach()
{
	owner = nullptr;
}
