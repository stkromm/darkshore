#pragma once

#include <string>

extern "C" {
# include "Lua/lua.h"
# include "Lua/lauxlib.h"
# include "Lua/lualib.h"
}
#include "LuaBridge/LuaBridge.h"

namespace scripting {
	namespace ScriptManager {
		bool init();
		void shutdown();
	}
}
class Script
{
public:
	Script(std::string file_path);
	~Script();
};

