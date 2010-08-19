#ifndef _PATHPLAN_H_
#define _PATHPLAN_H_

#include <vector>
#include "constants.h"
#include "astar.h"
#include "rrt.h"
#include <iostream>
#include <set>
#include <cmath>
#include <cstdio>

using namespace std;

class Pathplan
{
	protected:

		list<state> pathFull;  //full solution, showing possible partial branches
		list<state> pathFinal; //final solution, for path execution purposes

		int envRRT[MAX_X][MAX_Y]; //environment matrix for RRT
		Grid envAStar[MAX_X][MAX_Y]; //environment matrix for AStar
		int costAStar[MAX_X][MAX_Y];

		//----- Pathplans -----
		void runRRT(); //driver for RRT
		void runAStar(); //driver for AStar		

		//---- Functions ----
		void fillEnv_playerBox(int centerx, int centery, int safetyCells);	

	public:

		//---- Position on the field (in millimeters) ----
		Point initialpos;
		Point finalpos;

		//---- Constructor and Destructor ----
		Pathplan(Point initialpos, Point finalpos);
		Pathplan();
		~Pathplan();

		//----- Functions -----	
		Point getPathNode(int nodeIndex); //returns a specific node on pathFinal (initialState is 0)
		void runPathplan(int pathplanIndex=PATHPLAN_ASTAR);
		void fillEnv(vector<RP::Point> playersPositions); //fills the enviroment with positions of the obstacles (currently, only for players)
};


#endif
