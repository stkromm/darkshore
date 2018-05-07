#pragma once

extern "C" {
# include "lua/lua.h"
	// ReSharper disable once CppUnusedIncludeDirective
# include "lua/lauxlib.h"
	// ReSharper disable once CppUnusedIncludeDirective
# include "lua/lualib.h"
}

// ReSharper disable once CppUnusedIncludeDirective
#include "lua_bridge/LuaBridge.h"

namespace scripting
{
	static lua_State* lua_state;
}
