#pragma once

class object {
public:
	bool is_destroyed = false;
	virtual void on_spawn() {}
	virtual void tick() {}
	virtual void on_destroy() {}

	bool operator==(object obj) {
		return true;
	}

	void destroy() {
		is_destroyed = true;
	}
};