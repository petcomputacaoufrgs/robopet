
#include "point_userdata.h"
#include <new>

int Point_setX(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setX(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setX(double)");
lua_error(L); 
	}

}

int Point_setY(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setY(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setY(double)");
lua_error(L); 
	}

}

int Point_getDistanceX(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushnumber(L,c->getDistanceX(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method getDistanceX(Point)");
lua_error(L); 
	}

}

int Point_getDistance(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushnumber(L,c->getDistance(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method getDistance(Point)");
lua_error(L); 
	}

}

int Point_getDistanceY(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushnumber(L,c->getDistanceY(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method getDistanceY(Point)");
lua_error(L); 
	}

}

int Point_setXY(lua_State *L)
{	if( lua_isnumber(L,2) && lua_isnumber(L,3)) {

    Point *c = (Point*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
		double just_a_double1 =  lua_tonumber(L,3);
    c->setXY(just_a_double0,just_a_double1);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setXY(double,double)");
lua_error(L); 
	}

}

int Point_getX(lua_State *L)
{	
    Point *c = (Point*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getX());
    return 1;

}

int Point_getY(lua_State *L)
{	
    Point *c = (Point*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getY());
    return 1;

}
int Point_new(lua_State* L)
{
	size_t size = sizeof(Point);
	Point *p = (Point*) lua_newuserdata(L, size);
	new (p) Point();
	luaL_getmetatable(L, "Point");
	lua_setmetatable(L, -2);
	return 1;
}

int Point_gc(lua_State* L)
{
	Point *p = (Point*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg Pointlib[] = {
	{"new", Point_new},
	{NULL,NULL}
};


static const luaL_reg Point_meta[] = {
	{ "setX", Point_setX },
	{ "setY", Point_setY },
	{ "getDistanceX", Point_getDistanceX },
	{ "getDistance", Point_getDistance },
	{ "getDistanceY", Point_getDistanceY },
	{ "setXY", Point_setXY },
	{ "getX", Point_getX },
	{ "getY", Point_getY },
	{NULL,NULL}
};

int luaopen_Point(lua_State *L)
{
	luaL_newmetatable(L, "Point");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, Point_meta);
	luaL_register(L, "Point", Pointlib);
	return 1;
}


