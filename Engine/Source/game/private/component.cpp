#include "game/component.h"

using namespace ds::game;

Component::Component() : owner(nullptr)
{
}

Component::~Component() = default;


void Component::attach(Entity* entity)
{
	if (entity)
	{
		if (owner)
		{
			detach();
		}
		owner = entity;
		on_attach();
	}
}

void Component::detach()
{
	if (owner)
	{
		owner = nullptr;
		on_detach();
	}
}
