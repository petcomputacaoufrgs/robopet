
#ifndef __MOONBIND_VECTOR__H__
#define __MOONBIND_VECTOR__H__

#include "vector.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int Vector_angleCW(lua_State *L);
int Vector_angleDegrees(lua_State *L);
int Vector_angle(lua_State *L);
int Vector_myAngleDegrees(lua_State *L);
int Vector_angleCWDegrees(lua_State *L);
int Vector_perpendicular(lua_State *L);
int Vector_angleCCWDegrees(lua_State *L);
int Vector_linearlyDependent(lua_State *L);
int Vector_normalizeMe(lua_State *L);
int Vector_projection(lua_State *L);
int Vector_normalize(lua_State *L);
int Vector_myAngle(lua_State *L);
int Vector_rotate(lua_State *L);
int Vector_getNorm(lua_State *L);
int Vector_angleCCW(lua_State *L);
int Vector_dotProduct(lua_State *L);int Vector_new(lua_State* L);
int Vector_gc(lua_State* L);
int luaopen_Vector(lua_State *L);


#endif // __MOONBIND_VECTOR__H__
