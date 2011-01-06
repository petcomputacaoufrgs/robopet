
#include "vector_userdata.h"
#include <new>

int Vector_angleCW(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angleCW(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angleCW(Vector)");
lua_error(L); 
	}

}

int Vector_angleDegrees(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angleDegrees(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angleDegrees(Vector)");
lua_error(L); 
	}

}

int Vector_angle(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angle(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angle(Vector)");
lua_error(L); 
	}

}

int Vector_myAngleDegrees(lua_State *L)
{	
    Vector *c = (Vector*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->myAngleDegrees());
    return 1;

}

int Vector_angleCWDegrees(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angleCWDegrees(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angleCWDegrees(Vector)");
lua_error(L); 
	}

}

int Vector_perpendicular(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushboolean(L,c->perpendicular(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method perpendicular(Vector)");
lua_error(L); 
	}

}

int Vector_angleCCWDegrees(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angleCCWDegrees(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angleCCWDegrees(Vector)");
lua_error(L); 
	}

}

int Vector_linearlyDependent(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushboolean(L,c->linearlyDependent(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method linearlyDependent(Vector)");
lua_error(L); 
	}

}

int Vector_normalizeMe(lua_State *L)
{	
    Vector *c = (Vector*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->normalizeMe());
    return 1;

}

int Vector_projection(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushlightuserdata(L,(void*)&c->projection(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method projection(Vector)");
lua_error(L); 
	}

}

int Vector_normalize(lua_State *L)
{	
    Vector *c = (Vector*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->normalize());
    return 1;

}

int Vector_myAngle(lua_State *L)
{	
    Vector *c = (Vector*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->myAngle());
    return 1;

}

int Vector_rotate(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->rotate(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method rotate(double)");
lua_error(L); 
	}

}

int Vector_getNorm(lua_State *L)
{	
    Vector *c = (Vector*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getNorm());
    return 1;

}

int Vector_angleCCW(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angleCCW(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angleCCW(Vector)");
lua_error(L); 
	}

}

int Vector_dotProduct(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Vector *c = (Vector*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    lua_pushnumber(L,c->dotProduct(just_a_Vector0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method dotProduct(Vector)");
lua_error(L); 
	}

}
int Vector_new(lua_State* L)
{
	size_t size = sizeof(Vector);
	Vector *p = (Vector*) lua_newuserdata(L, size);
	new (p) Vector();
	luaL_getmetatable(L, "Vector");
	lua_setmetatable(L, -2);
	return 1;
}

int Vector_gc(lua_State* L)
{
	Vector *p = (Vector*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg Vectorlib[] = {
	{"new", Vector_new},
	{NULL,NULL}
};


static const luaL_reg Vector_meta[] = {
	{ "angleCW", Vector_angleCW },
	{ "angleDegrees", Vector_angleDegrees },
	{ "angle", Vector_angle },
	{ "myAngleDegrees", Vector_myAngleDegrees },
	{ "angleCWDegrees", Vector_angleCWDegrees },
	{ "perpendicular", Vector_perpendicular },
	{ "angleCCWDegrees", Vector_angleCCWDegrees },
	{ "linearlyDependent", Vector_linearlyDependent },
	{ "normalizeMe", Vector_normalizeMe },
	{ "projection", Vector_projection },
	{ "normalize", Vector_normalize },
	{ "myAngle", Vector_myAngle },
	{ "rotate", Vector_rotate },
	{ "getNorm", Vector_getNorm },
	{ "angleCCW", Vector_angleCCW },
	{ "dotProduct", Vector_dotProduct },
	{NULL,NULL}
};

int luaopen_Vector(lua_State *L)
{
	luaL_newmetatable(L, "Vector");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, Vector_meta);
	luaL_register(L, "Vector", Vectorlib);
	return 1;
}


