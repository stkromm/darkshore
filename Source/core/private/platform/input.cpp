#include "core/platform/input.h"

using namespace platform;

bool pressed_keys[1024];

bool platform::is_pressed(const uint32_t key)
{
	return pressed_keys[key];
}

void platform::set_pressed(const uint32_t key, const bool pressed)
{
	pressed_keys[key] = pressed;
}