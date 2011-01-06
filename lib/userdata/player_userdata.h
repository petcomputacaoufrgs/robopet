
#ifndef __MOONBIND_PLAYER__H__
#define __MOONBIND_PLAYER__H__

#include "player.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int Player_keepDistanceToBall(lua_State *L);
int Player_getKickerIntensity(lua_State *L);
int Player_pointTo(lua_State *L);
int Player_isPointingTo(lua_State *L);
int Player_stay(lua_State *L);
int Player_setDriblerIntensity(lua_State *L);
int Player_getCurrentAngle(lua_State *L);
int Player_calcDeltaAngle(lua_State *L);
int Player_getDriblerIntensity(lua_State *L);
int Player_getRole(lua_State *L);
int Player_setRole(lua_State *L);
int Player_setAngle(lua_State *L);
int Player_getDeltaAngle(lua_State *L);
int Player_getFutureAngle(lua_State *L);
int Player_isDribling(lua_State *L);
int Player_setId(lua_State *L);
int Player_setFutureAngle(lua_State *L);
int Player_kick(lua_State *L);
int Player_setKickerIntensity(lua_State *L);
int Player_setCurrentAngle(lua_State *L);
int Player_isKicking(lua_State *L);
int Player_setDeltaAngle(lua_State *L);
int Player_getDisplacementWithBall(lua_State *L);
int Player_getAngle(lua_State *L);
int Player_setDisplacementWithBall(lua_State *L);
int Player_getId(lua_State *L);int Player_new(lua_State* L);
int Player_gc(lua_State* L);
int luaopen_Player(lua_State *L);


#endif // __MOONBIND_PLAYER__H__
