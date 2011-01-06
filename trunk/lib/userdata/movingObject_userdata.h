
#ifndef __MOONBIND_MOVINGOBJECT__H__
#define __MOONBIND_MOVINGOBJECT__H__

#include "movingObject.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int MovingObject_setX(lua_State *L);
int MovingObject_setY(lua_State *L);
int MovingObject_getDistance(lua_State *L);
int MovingObject_setCurrentPosition(lua_State *L);
int MovingObject_getPosition(lua_State *L);
int MovingObject_getFuturePosition(lua_State *L);
int MovingObject_setDisplacement(lua_State *L);
int MovingObject_setFuturePositionX(lua_State *L);
int MovingObject_setFuturePositionY(lua_State *L);
int MovingObject_setCurrentPositionX(lua_State *L);
int MovingObject_getDisplacement(lua_State *L);
int MovingObject_setCurrentPositionY(lua_State *L);
int MovingObject_getCurrentPosition(lua_State *L);
int MovingObject_calcDisplacementVector(lua_State *L);
int MovingObject_getX(lua_State *L);
int MovingObject_setFuturePosition(lua_State *L);
int MovingObject_getY(lua_State *L);
int MovingObject_getPastPosition(lua_State *L);
int MovingObject_calculateDisplacement(lua_State *L);
int MovingObject_setPastPositionX(lua_State *L);
int MovingObject_setPastPosition(lua_State *L);
int MovingObject_setPastPositionY(lua_State *L);int MovingObject_new(lua_State* L);
int MovingObject_gc(lua_State* L);
int luaopen_MovingObject(lua_State *L);


#endif // __MOONBIND_MOVINGOBJECT__H__
