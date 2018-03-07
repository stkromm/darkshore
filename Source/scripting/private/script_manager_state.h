#pragma once

extern "C" {
# include "Lua/lua.h"
# include "Lua/lauxlib.h"
# include "Lua/lualib.h"
}
#include "LuaBridge/LuaBridge.h"

namespace scripting {
	static lua_State* lua_state;
}