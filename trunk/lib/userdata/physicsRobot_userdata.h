
#ifndef __MOONBIND_PHYSICSROBOT__H__
#define __MOONBIND_PHYSICSROBOT__H__

#include "physicsRobot.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int PhysicsRobot_stop(lua_State *L);
int PhysicsRobot_move(lua_State *L);
int PhysicsRobot_rotate(lua_State *L);
int PhysicsRobot_go(lua_State *L);
int PhysicsRobot_fakeMove(lua_State *L);
int PhysicsRobot_getAngle(lua_State *L);
int PhysicsRobot_update(lua_State *L);int PhysicsRobot_new(lua_State* L);
int PhysicsRobot_gc(lua_State* L);
int luaopen_PhysicsRobot(lua_State *L);


#endif // __MOONBIND_PHYSICSROBOT__H__
