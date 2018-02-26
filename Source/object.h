#pragma once

#include "transform.h"

class GameObject {
public:
	bool is_destroyed = false;
	virtual void on_spawn() {}
	virtual void tick() {}
	virtual void on_destroy() {}

	bool operator==(GameObject obj) {
		return true;
	}

	void destroy() {
		is_destroyed = true;
	}
};