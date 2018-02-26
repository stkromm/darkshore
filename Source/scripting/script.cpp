#include "script.h"

using namespace scripting;

static lua_State* lua_state;

bool ScriptManager::init()
{
	lua_state = luaL_newstate();
	return true;
}

void ScriptManager::shutdown()
{
}

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
