#pragma once
#include <string>
#include <memory>

class Entity;

struct ComponentType
{
	std::string name;
};

class Component
{
private:
	Entity* owner;

public:
	Component();
	~Component();

	Entity* get_owner() const
	{
		return owner;
	}

	void attach(Entity* entity)
	{
		owner = entity;
		on_attach();
	}

	virtual void on_attach()
	{

	}

	void detach()
	{
		owner = nullptr;
	}

	bool is_attached() const 
	{
		return owner != nullptr;
	}
};

