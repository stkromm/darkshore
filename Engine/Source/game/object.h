#pragma once

#include <string>

namespace ds
{
	namespace game
	{
class Game;

class GameObject
{
protected:
	std::string tag = "";
	Game* game = nullptr;
public:
	virtual ~GameObject() = default;
	bool is_destroyed = false;

	virtual void on_spawn()
	{
	}

	virtual void tick()
	{
	}

	virtual void self_tick()
	{
	}

	virtual void on_destroy()
	{
	}

	bool operator==(const GameObject& obj) const
	{
		// TODO Implement
		return true;
	}

	void destroy()
	{
		is_destroyed = true;
	}

	std::string get_tag()
	{
		return tag;
	}

	void set_game(Game* game)
	{
		this->game = game;
	}
};


	}
}