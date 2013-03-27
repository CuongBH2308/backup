// how to compile:
// g++ lua1.cpp -llua -ldl

#include <stdio.h>
#include "NPCManager.h"
#include "NPCObject.h"
extern "C"
{
#include <lua.h>
#include <lauxlib.h>

#include <lualib.h> // lua libraries
}

int l_addNPC(lua_State* luaVM)
{
	NPCManager::get()->addNPC(lua_tostring(luaVM, -1));
	lua_pushnumber(luaVM, 0);
	return 1;
}

int l_removeNPC(lua_State* luaVM)
{
	const char* name = lua_tostring(luaVM, -1);
	NPCManager::get()->removeNPC(name);
	lua_pushnumber(luaVM, 0);
	return 1;
} 

void execute_simple_string(lua_State* luaVM)
{
	const char* strLuaInput = "a = 1 + 1;\nprint(a);\n";
	luaL_dostring(luaVM, strLuaInput);
}


void execute_simple_file(lua_State* luaVM)
{
	// load a startup lua file
	luaL_dofile(luaVM, "./startup.lua");
	luaL_dofile(luaVM, "./startup.lua");

	// load a startup binary lua file
	luaL_dofile(luaVM, "./startup.lub");
}


void execute_game_logic(lua_State* luaVM)
{
	lua_register(luaVM, "addNPC", l_addNPC);
	lua_register(luaVM, "removeNPC", l_removeNPC);

	luaL_dofile(luaVM, "./gamelogic.lua");
	
	NPCManager::get()->dump();
}

int main(int argc, char* argv[])
{
	lua_State* luaVM = luaL_newstate();

	if(NULL == luaVM)
	{
		printf("Error Initializing lua\n");
		return -1;
	}

	// initialize lua standard library functions
	luaL_openlibs(luaVM);

	// do stuff with lua code
	execute_simple_string(luaVM);

	execute_simple_file(luaVM);

	execute_game_logic(luaVM);


	lua_close(luaVM);

	return 0;

}
