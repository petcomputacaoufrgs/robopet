#include "luaCppBridge.h"

LuaCppBridge::LuaCppBridge()
{
	
	
	
}

LuaCppBridge::~LuaCppBridge() {}

void LuaCppBridge::setMyTeam(int team)
{
	myTeam = team;
}

void LuaCppBridge::setPlayerRole(int index, char role[])
{
	//printf("role %i: %s\n",index,role);
	sprintf(playerRoles[index-1],"%s",role);
}

int LuaCppBridge::getMyTeam()
{
	return myTeam;
}
