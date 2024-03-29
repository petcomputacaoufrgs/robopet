#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#include "constants.h"
#include "utils.h"
#include "player.h"


#define MAXC 64

/**
 * Wrapper class for info to be trade between Lua and Cpp.
 * \ingroup RoboPETLib
 * */
 
class LuaCppBridge
{
	public:
		LuaCppBridge();
		~LuaCppBridge();
		
		int 	*myTeam;
		char 	playerRoles[MAX_PLAYERS][MAXC];
		bool	ballObstacle;
		int		playerBallObstacle;
		
		//Attributes can be accessed only by functions within Lua
		void 	setMyTeam(int *team);
		void 	setPlayerRole(int index, char role[]);
		int 	getMyTeam();
		void setBallAsObstacle(bool isObstacle, int p);
	
};
