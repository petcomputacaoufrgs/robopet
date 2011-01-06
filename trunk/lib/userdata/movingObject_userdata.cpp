
#include "movingObject_userdata.h"
#include <new>

int MovingObject_setX(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setX(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setX(double)");
lua_error(L); 
	}

}

int MovingObject_setY(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setY(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setY(double)");
lua_error(L); 
	}

}

int MovingObject_getDistance(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	MovingObject just_a_MovingObject0 = *(MovingObject*) lua_touserdata(L,2);
    lua_pushnumber(L,c->getDistance(just_a_MovingObject0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method getDistance(MovingObject)");
lua_error(L); 
	}

}

int MovingObject_setCurrentPosition(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    c->setCurrentPosition(just_a_Point0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setCurrentPosition(Point)");
lua_error(L); 
	}

}

int MovingObject_getPosition(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getPosition());
    return 1;

}

int MovingObject_getFuturePosition(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getFuturePosition());
    return 1;

}

int MovingObject_setDisplacement(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setDisplacement(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setDisplacement(double)");
lua_error(L); 
	}

}

int MovingObject_setFuturePositionX(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setFuturePositionX(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setFuturePositionX(double)");
lua_error(L); 
	}

}

int MovingObject_setFuturePositionY(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setFuturePositionY(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setFuturePositionY(double)");
lua_error(L); 
	}

}

int MovingObject_setCurrentPositionX(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setCurrentPositionX(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setCurrentPositionX(double)");
lua_error(L); 
	}

}

int MovingObject_getDisplacement(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getDisplacement());
    return 1;

}

int MovingObject_setCurrentPositionY(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setCurrentPositionY(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setCurrentPositionY(double)");
lua_error(L); 
	}

}

int MovingObject_getCurrentPosition(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getCurrentPosition());
    return 1;

}

int MovingObject_calcDisplacementVector(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->calcDisplacementVector());
    return 1;

}

int MovingObject_getX(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getX());
    return 1;

}

int MovingObject_setFuturePosition(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    c->setFuturePosition(just_a_Point0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setFuturePosition(Point)");
lua_error(L); 
	}

}

int MovingObject_getY(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getY());
    return 1;

}

int MovingObject_getPastPosition(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    lua_pushlightuserdata(L,(void*)&c->getPastPosition());
    return 1;

}

int MovingObject_calculateDisplacement(lua_State *L)
{	
    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    
    c->calculateDisplacement();
    return 0;

}

int MovingObject_setPastPositionX(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setPastPositionX(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setPastPositionX(double)");
lua_error(L); 
	}

}

int MovingObject_setPastPosition(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    c->setPastPosition(just_a_Point0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setPastPosition(Point)");
lua_error(L); 
	}

}

int MovingObject_setPastPositionY(lua_State *L)
{	if( lua_isnumber(L,2)) {

    MovingObject *c = (MovingObject*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setPastPositionY(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setPastPositionY(double)");
lua_error(L); 
	}

}
int MovingObject_new(lua_State* L)
{
	size_t size = sizeof(MovingObject);
	MovingObject *p = (MovingObject*) lua_newuserdata(L, size);
	new (p) MovingObject();
	luaL_getmetatable(L, "MovingObject");
	lua_setmetatable(L, -2);
	return 1;
}

int MovingObject_gc(lua_State* L)
{
	MovingObject *p = (MovingObject*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg MovingObjectlib[] = {
	{"new", MovingObject_new},
	{NULL,NULL}
};


static const luaL_reg MovingObject_meta[] = {
	{ "setX", MovingObject_setX },
	{ "setY", MovingObject_setY },
	{ "getDistance", MovingObject_getDistance },
	{ "setCurrentPosition", MovingObject_setCurrentPosition },
	{ "getPosition", MovingObject_getPosition },
	{ "getFuturePosition", MovingObject_getFuturePosition },
	{ "setDisplacement", MovingObject_setDisplacement },
	{ "setFuturePositionX", MovingObject_setFuturePositionX },
	{ "setFuturePositionY", MovingObject_setFuturePositionY },
	{ "setCurrentPositionX", MovingObject_setCurrentPositionX },
	{ "getDisplacement", MovingObject_getDisplacement },
	{ "setCurrentPositionY", MovingObject_setCurrentPositionY },
	{ "getCurrentPosition", MovingObject_getCurrentPosition },
	{ "calcDisplacementVector", MovingObject_calcDisplacementVector },
	{ "getX", MovingObject_getX },
	{ "setFuturePosition", MovingObject_setFuturePosition },
	{ "getY", MovingObject_getY },
	{ "getPastPosition", MovingObject_getPastPosition },
	{ "calculateDisplacement", MovingObject_calculateDisplacement },
	{ "setPastPositionX", MovingObject_setPastPositionX },
	{ "setPastPosition", MovingObject_setPastPosition },
	{ "setPastPositionY", MovingObject_setPastPositionY },
	{NULL,NULL}
};

int luaopen_MovingObject(lua_State *L)
{
	luaL_newmetatable(L, "MovingObject");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, MovingObject_meta);
	luaL_register(L, "MovingObject", MovingObjectlib);
	return 1;
}


