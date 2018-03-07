#pragma once

#include <string>

class Game;

class GameObject {
protected:
	std::string tag = "";
	Game* game;
public:
	bool is_destroyed = false;
	virtual void on_spawn() {}
	virtual void tick() {}
	virtual void self_tick() {}
	virtual void on_destroy() {}

	bool operator==(GameObject obj) {
		// TODO Implement
		return true;
	}

	void destroy() {
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