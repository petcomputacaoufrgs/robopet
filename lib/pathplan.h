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


#define CELLS_PER_MM  MAX_X / (float) FIELD_WIDTH //MAX_X and MAX_Y are dimensions from the matrix on rrt.h
#define MM_PER_CELLS  FIELD_WIDTH / (float) MAX_X

#define MM_TO_CELLS(x) ((x) * (CELLS_PER_MM))

#define CELLS_TO_MM(x) ((x) * (MM_PER_CELLS))


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

		//---- Functions ----
		void fillEnv_playerBox(int centerx, int centery, int safetyCells);

	public:
		//---- Constructor and Destructor ----
		Pathplan(Point initialpos, Point finalpos);
		Pathplan();
		~Pathplan();

		//---- Position on the field (in grid coordinates) ----
		Point initialpos;
		Point finalpos;

		list<Point> pathFull;  //full solution, showing possible partial branches
		list<Point> pathFinal; //final solution, for path execution purposes (next point to visit)
		envType env[MAX_X][MAX_Y]; //generic environment matrix

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
