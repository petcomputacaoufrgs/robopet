
#include "player_userdata.h"
#include <new>

int Player_keepDistanceToBall(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->keepDistanceToBall(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method keepDistanceToBall(double)");
lua_error(L); 
	}

}

int Player_getKickerIntensity(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getKickerIntensity());
    return 1;

}

int Player_pointTo(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    c->pointTo(just_a_Point0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method pointTo(Point)");
lua_error(L); 
	}

}

int Player_isPointingTo(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	Point just_a_Point0 = *(Point*) lua_touserdata(L,2);
    lua_pushboolean(L,c->isPointingTo(just_a_Point0));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method isPointingTo(Point)");
lua_error(L); 
	}

}

int Player_stay(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    c->stay();
    return 0;

}

int Player_setDriblerIntensity(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
    c->setDriblerIntensity(just_a_int0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setDriblerIntensity(int)");
lua_error(L); 
	}

}

int Player_getCurrentAngle(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getCurrentAngle());
    return 1;

}

int Player_calcDeltaAngle(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->calcDeltaAngle());
    return 1;

}

int Player_getDriblerIntensity(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getDriblerIntensity());
    return 1;

}

int Player_getRole(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getRole());
    return 1;

}

int Player_setRole(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
    c->setRole(just_a_int0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setRole(int)");
lua_error(L); 
	}

}

int Player_setAngle(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setAngle(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setAngle(double)");
lua_error(L); 
	}

}

int Player_getDeltaAngle(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getDeltaAngle());
    return 1;

}

int Player_getFutureAngle(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getFutureAngle());
    return 1;

}

int Player_isDribling(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushboolean(L,c->isDribling());
    return 1;

}

int Player_setId(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
    c->setId(just_a_int0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setId(int)");
lua_error(L); 
	}

}

int Player_setFutureAngle(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setFutureAngle(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setFutureAngle(double)");
lua_error(L); 
	}

}

int Player_kick(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    c->kick();
    return 0;

}

int Player_setKickerIntensity(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
    c->setKickerIntensity(just_a_int0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setKickerIntensity(int)");
lua_error(L); 
	}

}

int Player_setCurrentAngle(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setCurrentAngle(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setCurrentAngle(double)");
lua_error(L); 
	}

}

int Player_isKicking(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushboolean(L,c->isKicking());
    return 1;

}

int Player_setDeltaAngle(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setDeltaAngle(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setDeltaAngle(double)");
lua_error(L); 
	}

}

int Player_getDisplacementWithBall(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getDisplacementWithBall());
    return 1;

}

int Player_getAngle(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getAngle());
    return 1;

}

int Player_setDisplacementWithBall(lua_State *L)
{	if( lua_isnumber(L,2)) {

    Player *c = (Player*) lua_touserdata(L,1);
    	double just_a_double0 =  lua_tonumber(L,2);
    c->setDisplacementWithBall(just_a_double0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method setDisplacementWithBall(double)");
lua_error(L); 
	}

}

int Player_getId(lua_State *L)
{	
    Player *c = (Player*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getId());
    return 1;

}
int Player_new(lua_State* L)
{
	size_t size = sizeof(Player);
	Player *p = (Player*) lua_newuserdata(L, size);
	new (p) Player();
	luaL_getmetatable(L, "Player");
	lua_setmetatable(L, -2);
	return 1;
}

int Player_gc(lua_State* L)
{
	Player *p = (Player*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg Playerlib[] = {
	{"new", Player_new},
	{NULL,NULL}
};


static const luaL_reg Player_meta[] = {
	{ "keepDistanceToBall", Player_keepDistanceToBall },
	{ "getKickerIntensity", Player_getKickerIntensity },
	{ "pointTo", Player_pointTo },
	{ "isPointingTo", Player_isPointingTo },
	{ "stay", Player_stay },
	{ "setDriblerIntensity", Player_setDriblerIntensity },
	{ "getCurrentAngle", Player_getCurrentAngle },
	{ "calcDeltaAngle", Player_calcDeltaAngle },
	{ "getDriblerIntensity", Player_getDriblerIntensity },
	{ "getRole", Player_getRole },
	{ "setRole", Player_setRole },
	{ "setAngle", Player_setAngle },
	{ "getDeltaAngle", Player_getDeltaAngle },
	{ "getFutureAngle", Player_getFutureAngle },
	{ "isDribling", Player_isDribling },
	{ "setId", Player_setId },
	{ "setFutureAngle", Player_setFutureAngle },
	{ "kick", Player_kick },
	{ "setKickerIntensity", Player_setKickerIntensity },
	{ "setCurrentAngle", Player_setCurrentAngle },
	{ "isKicking", Player_isKicking },
	{ "setDeltaAngle", Player_setDeltaAngle },
	{ "getDisplacementWithBall", Player_getDisplacementWithBall },
	{ "getAngle", Player_getAngle },
	{ "setDisplacementWithBall", Player_setDisplacementWithBall },
	{ "getId", Player_getId },
	{NULL,NULL}
};

int luaopen_Player(lua_State *L)
{
	luaL_newmetatable(L, "Player");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, Player_meta);
	luaL_register(L, "Player", Playerlib);
	return 1;
}


