#pragma once

class Entity;

class Component
{
private:
	Entity* owner;

public:
	Component();
	virtual ~Component();

	virtual void on_attach() {}
	virtual void on_detach() {}

	Entity* get_owner() const
	{
		return owner;
	}

	bool is_attached() const
	{
		return owner != nullptr;
	}

	void attach(Entity* entity);

	void detach();
};
