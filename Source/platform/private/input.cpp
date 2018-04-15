#include "platform/input.h"

using namespace platform;

bool pressed_keys[1024];

bool platform::is_pressed(uint32_t key)
{
	return pressed_keys[key];
}

void platform::set_pressed(uint32_t key, bool pressed)
{
	pressed_keys[key] = pressed;
}