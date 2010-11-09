/*
	Lua bindings for class Vector
	This file was automatically generated by cpptolua

*/

#include "vector.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"

}

int Vector_projection(lua_State* L);
int Vector_perpendicular(lua_State* L);
int Vector_angleClockwise(lua_State* L);
int Vector_angleDegrees(lua_State* L);
int Vector_angle(lua_State* L);
int Vector_rotate(lua_State* L);
int Vector_dotProduct(lua_State* L);
int Vector_linearlyDependent(lua_State* L);
int Vector_normalizeMe(lua_State* L);
int Vector_normalize(lua_State* L);
int Vector_getNorm(lua_State* L);
Vector* toVector(lua_State *L, int index);
Vector* checkVector(lua_State *L, int index);
int copyVector(lua_State *L, Vector *p);
int luaopen_Vector(lua_State *L);
