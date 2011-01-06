
#ifndef __MOONBIND_POINT__H__
#define __MOONBIND_POINT__H__

#include "point.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int Point_setX(lua_State *L);
int Point_setY(lua_State *L);
int Point_getDistanceX(lua_State *L);
int Point_getDistance(lua_State *L);
int Point_getDistanceY(lua_State *L);
int Point_setXY(lua_State *L);
int Point_getX(lua_State *L);
int Point_getY(lua_State *L);int Point_new(lua_State* L);
int Point_gc(lua_State* L);
int luaopen_Point(lua_State *L);


#endif // __MOONBIND_POINT__H__
