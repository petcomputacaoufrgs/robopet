
#include "physicsRobot_userdata.h"
#include <new>

int PhysicsRobot_stop(lua_State *L)
{	
    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    
    c->stop();
    return 0;

}

int PhysicsRobot_move(lua_State *L)
{	if( lua_isnumber(L,2) && lua_isuserdata(L,3)) {

    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
		Vector just_a_Vector1 = *(Vector*) lua_touserdata(L,3);
    c->move(just_a_int0,just_a_Vector1);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method move(int,Vector)");
lua_error(L); 
	}

}

int PhysicsRobot_rotate(lua_State *L)
{	if( lua_isnumber(L,2)) {

    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    	int just_a_int0 =  lua_tonumber(L,2);
    c->rotate(just_a_int0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method rotate(int)");
lua_error(L); 
	}

}

int PhysicsRobot_go(lua_State *L)
{	if( lua_isuserdata(L,2)) {

    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    	Vector just_a_Vector0 = *(Vector*) lua_touserdata(L,2);
    c->go(just_a_Vector0);
    return 0;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method go(Vector)");
lua_error(L); 
	}

}

int PhysicsRobot_fakeMove(lua_State *L)
{	if( lua_isnumber(L,2) && lua_isboolean(L,3) && lua_isnumber(L,4) && lua_isnumber(L,5) && lua_isuserdata(L,6)) {

    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    	float just_a_float0 =  lua_tonumber(L,2);
		bool just_a_bool1 =  lua_toboolean(L,3);
		int just_a_int2 =  lua_tonumber(L,4);
		int just_a_int3 =  lua_tonumber(L,5);
		Vector just_a_Vector4 = *(Vector*) lua_touserdata(L,6);
    lua_pushlightuserdata(L,(void*)&c->fakeMove(just_a_float0,just_a_bool1,just_a_int2,just_a_int3,just_a_Vector4));
    return 1;

	} else {
 	lua_pushstring(L,"Incompatible parameters for method fakeMove(float,bool,int,int,Vector)");
lua_error(L); 
	}

}

int PhysicsRobot_getAngle(lua_State *L)
{	
    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    
    lua_pushnumber(L,c->getAngle());
    return 1;

}

int PhysicsRobot_update(lua_State *L)
{	
    PhysicsRobot *c = (PhysicsRobot*) lua_touserdata(L,1);
    
    c->update();
    return 0;

}
int PhysicsRobot_new(lua_State* L)
{
	size_t size = sizeof(PhysicsRobot);
	PhysicsRobot *p = (PhysicsRobot*) lua_newuserdata(L, size);
	new (p) PhysicsRobot();
	luaL_getmetatable(L, "PhysicsRobot");
	lua_setmetatable(L, -2);
	return 1;
}

int PhysicsRobot_gc(lua_State* L)
{
	PhysicsRobot *p = (PhysicsRobot*) lua_touserdata(L,1);
	if (p) delete p;
		return 0;
}


const struct luaL_reg PhysicsRobotlib[] = {
	{"new", PhysicsRobot_new},
	{NULL,NULL}
};


static const luaL_reg PhysicsRobot_meta[] = {
	{ "stop", PhysicsRobot_stop },
	{ "move", PhysicsRobot_move },
	{ "rotate", PhysicsRobot_rotate },
	{ "go", PhysicsRobot_go },
	{ "fakeMove", PhysicsRobot_fakeMove },
	{ "getAngle", PhysicsRobot_getAngle },
	{ "update", PhysicsRobot_update },
	{NULL,NULL}
};

int luaopen_PhysicsRobot(lua_State *L)
{
	luaL_newmetatable(L, "PhysicsRobot");
	
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, PhysicsRobot_meta);
	luaL_register(L, "PhysicsRobot", PhysicsRobotlib);
	return 1;
}


