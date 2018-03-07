#include "scripting/script.h"
#include "scripting/private/script_manager_state.h"

using namespace scripting;

Script::Script(std::string file_path)
{
	luaL_dofile(lua_state, file_path.c_str());
	luaL_openlibs(lua_state);
	lua_pcall(lua_state, 0, 0, 0);
	//luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
	//luabridge::LuaRef n = luabridge::getGlobal(L, "number");
	//std::string luaString = s.cast<std::string>();
	//int answer = n.cast<int>();
}

Script::~Script()
{
}
