#include "platform/input.h"

using namespace ds::platform;

bool pressed_keys[1024];

bool is_pressed(const uint32_t key)
{
	return pressed_keys[key];
}

void set_pressed(const uint32_t key, const bool pressed)
{
	pressed_keys[key] = pressed;
}