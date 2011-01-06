
#include "line_userdata.h"
#include <new>

int Line_parallel(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Line just_a_Line0 = *(Line*) lua_touserdata(L,2);
    lua_pushboolean(L,c->parallel(just_a_Line0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method parallel(Line)");
lua_error(L); 
	}

}

int Line_getAngularCoefficient(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getAngularCoefficient());
    return 1;

}

int Line_angle(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Line just_a_Line0 = *(Line*) lua_touserdata(L,2);
    lua_pushnumber(L,c->angle(just_a_Line0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method angle(Line)");
lua_error(L); 
	}

}

int Line_vertical(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushboolean(L,c->vertical());
    return 1;

}

int Line_intersects(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Line just_a_Line0 = *(Line*) lua_touserdata(L,2);
    lua_pushboolean(L,c->intersects(just_a_Line0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method intersects(Line)");
lua_error(L); 
	}

}

int Line_perpendicular(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Line just_a_Line0 = *(Line*) lua_touserdata(L,2);
    lua_pushboolean(L,c->perpendicular(just_a_Line0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method perpendicular(Line)");
lua_error(L); 
	}

}

int Line_setLinearCoefficient(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setLinearCoefficient(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setLinearCoefficient(double)");
lua_error(L); 
	}

}

int Line_setPoint(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    c->setPoint(just_a_Point0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setPoint(Point)");
lua_error(L); 
	}

}

int Line_preImage(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    lua_pushnumber(L,c->preImage(just_a_double0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method preImage(double)");
lua_error(L); 
	}

}

int Line_horizontal(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushboolean(L,c->horizontal());
    return 1;

}

int Line_getPoint(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getPoint());
    return 1;

}

int Line_setVector(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    c->setVector(just_a_Vector0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setVector(Vector)");
lua_error(L); 
	}

}

int Line_getVector(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getVector());
    return 1;

}

int Line_getLinearCoefficient(lua_State *L)
{	
    Line *c = (Line*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getLinearCoefficient());
    return 1;

}

int Line_image(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    lua_pushnumber(L,c->image(just_a_double0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method image(double)");
lua_error(L); 
	}

}

int Line_contains(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushboolean(L,c->contains(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method contains(Point)");
lua_error(L); 
	}

}

int Line_intersection(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Line just_a_Line0 = *(Line*) lua_touserdata(L,2);
    lua_pushlightuserdata(L,(void*)&c->intersection(just_a_Line0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method intersection(Line)");
lua_error(L); 
	}

}

int Line_distance(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushnumber(L,c->distance(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method distance(Point)");
lua_error(L); 
	}

}

int Line_setAngularCoefficient(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Line *c = (Line*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setAngularCoefficient(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setAngularCoefficient(double)");
lua_error(L); 
	}

}
int Line_new(lua_State* L)
{
	size_t size = sizeof(Line);
	Line *p = (Line*) lua_newuserdata(L, size);
	new (p) Line();
	luaL_getmetatable(L, "Line");
	lua_setmetatable(L, -2);
	return 1;
}

int Line_gc(lua_State* L)
{
	Line *p = (Line*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg Linelib[] = {
	{"new", Line_new},
	{NULL,NULL}
};


static const luaL_reg Line_meta[] = {
	{ "parallel", Line_parallel },
	{ "getAngularCoefficient", Line_getAngularCoefficient },
	{ "angle", Line_angle },
	{ "vertical", Line_vertical },
	{ "intersects", Line_intersects },
	{ "perpendicular", Line_perpendicular },
	{ "setLinearCoefficient", Line_setLinearCoefficient },
	{ "setPoint", Line_setPoint },
	{ "preImage", Line_preImage },
	{ "horizontal", Line_horizontal },
	{ "getPoint", Line_getPoint },
	{ "setVector", Line_setVector },
	{ "getVector", Line_getVector },
	{ "getLinearCoefficient", Line_getLinearCoefficient },
	{ "image", Line_image },
	{ "contains", Line_contains },
	{ "intersection", Line_intersection },
	{ "distance", Line_distance },
	{ "setAngularCoefficient", Line_setAngularCoefficient },
	{NULL,NULL}
};

int luaopen_Line(lua_State *L)
{
	luaL_newmetatable(L, "Line");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, Line_meta);
	luaL_register(L, "Line", Linelib);
	return 1;
}


