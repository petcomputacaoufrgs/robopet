#ifndef _PATHPLAN_H_
#define _PATHPLAN_H_

#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>

#include "constants.h"
#include "player.h"
#include "point.h"

using RP::Point;
using namespace std;


enum pathplanType
{
	RRT, ASTAR
};

enum envType
{
	FREE, OBSTACLE,	MARKER, NODE, PATH
};


class Pathplan
{
	protected:

		//---- Position on the field (in grid coordinates) ----
		Point initialpos;
		Point finalpos;

		list<Point> pathFull;  //full solution, showing possible partial branches
		list<Point> pathFinal; //final solution, for path execution purposes (next point to visit)
		envType env[MAX_X][MAX_Y]; //generic environment matrix

		//---- Functions ----
		void fillEnv_playerBox(int centerx, int centery, int safetyCells);

	public:
		//---- Constructor and Destructor ----
		Pathplan(Point initialpos, Point finalpos);
		Pathplan();
		~Pathplan();

		//----- Functions -----
		Point getPathNode(int nodeIndex); //returns a specific node on pathFinal (initialState is 0)
		void fillEnv(vector<RP::Point> playersPositions); //fills the enviroment with positions of the obstacles (currently, only for players)

		/* For debuging purposes. 
		 * Prints the actual environment
		 */
		void printEnv();
		
		virtual void run() {};

		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
};


#endif
