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
	strcpy(playerRoles[index],role);
}

int LuaCppBridge::getMyTeam()
{
	return myTeam;
}
