#pragma once

extern "C" {
# include "Lua/lua.h"
	// ReSharper disable once CppUnusedIncludeDirective
# include "Lua/lauxlib.h"
	// ReSharper disable once CppUnusedIncludeDirective
# include "Lua/lualib.h"
}

// ReSharper disable once CppUnusedIncludeDirective
#include "LuaBridge/LuaBridge.h"

namespace scripting
{
	static lua_State* lua_state;
}
