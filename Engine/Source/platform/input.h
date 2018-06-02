#pragma once

#include "platform.h"

namespace ds {
	namespace platform {
		bool is_pressed(uint32_t key);
		void set_pressed(uint32_t key, bool pressed);
	}
}