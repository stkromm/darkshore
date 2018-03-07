#include "scripting/script_manager.h"
#include "scripting/private/script_manager_state.h"

using namespace scripting;

bool ScriptManager::init()
{
	lua_state = luaL_newstate();
	return true;
}

void ScriptManager::shutdown()
{
}