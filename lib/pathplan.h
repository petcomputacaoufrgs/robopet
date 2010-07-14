#ifndef __ROBOPET_PATHPLAN_H__
#define __ROBOPET_PATHPLAN_H__

#include <vector>

#include "point.h"
#include "constants.h"

#include "rrt.h"



class Pathplan
{
	protected:
		list<state> pathFull;  //full solution, showing possible partial branches
		list<state> pathFinal; //final solution, for path execution purposes

		int env[MAX_X][MAX_Y]; //environment matrix
		
		
		void fillEnv_playerBox(int centerx, int centery, int safetyCells);
	
		void runRRT(); //driver for RRT

	public:
		//positions are, by convention, in milimeters
		Point initialpos;
		Point finalpos;


		//FUNCTIONS
		Pathplan();
		Pathplan(Point initialpos, Point finalpos);
		~Pathplan();
		
		
		Point getPathNode(int nodeIndex); //returns a specific node on pathFinal (initialState is 0)
		
		
		void runPathplan( int pathplanIndex=PATHPLAN_RRT );
		
		void fillEnv(vector<Point> playersPositions); //fills the enviroment with positions of the obstacles (currently, only for players)



};


#endif
