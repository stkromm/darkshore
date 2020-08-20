#include "platform/input.h"

bool pressed_keys[1024];

bool ds::platform::is_pressed(const uint32_t key)
{
	return pressed_keys[key];
}

void ds::platform::set_pressed(const uint32_t key, const bool pressed)
{
	pressed_keys[key] = pressed;
}