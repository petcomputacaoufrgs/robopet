
#ifndef __MOONBIND_LINE__H__
#define __MOONBIND_LINE__H__

#include "line.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int Line_parallel(lua_State *L);
int Line_getAngularCoefficient(lua_State *L);
int Line_angle(lua_State *L);
int Line_vertical(lua_State *L);
int Line_intersects(lua_State *L);
int Line_perpendicular(lua_State *L);
int Line_setLinearCoefficient(lua_State *L);
int Line_setPoint(lua_State *L);
int Line_preImage(lua_State *L);
int Line_horizontal(lua_State *L);
int Line_getPoint(lua_State *L);
int Line_setVector(lua_State *L);
int Line_getVector(lua_State *L);
int Line_getLinearCoefficient(lua_State *L);
int Line_image(lua_State *L);
int Line_contains(lua_State *L);
int Line_intersection(lua_State *L);
int Line_distance(lua_State *L);
int Line_setAngularCoefficient(lua_State *L);int Line_new(lua_State* L);
int Line_gc(lua_State* L);
int luaopen_Line(lua_State *L);


#endif // __MOONBIND_LINE__H__
