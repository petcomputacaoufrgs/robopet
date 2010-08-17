#ifndef __ROBOPET_PATHPLAN_H__
#define __ROBOPET_PATHPLAN_H__

#include <vector>
#include "point.h"
#include "grid.h"
#include "constants.h"
#include "rrt.h"
#include <iostream>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

//RLDU3791

enum
{
	RIGHT, //0
	LEFT,  //1
	DOWN,  //2
	UP,    //3
	RIGHT_DOWN, //4
	LEFT_UP,//5
	RIGHT_UP, //6
	LEFT_DOWN, //7
	NUM_NEIGHBORS //8
};

inline int INDEX(Point p) { return p.getX() + (p.getY() * MAX_X); }
inline bool IS_BOTTOM_BORDER(Point p) { return ( INDEX(p) / MAX_Y == MAX_Y - 1) ? true : false; }
inline bool IS_UPPER_BORDER(Point p) { return ( INDEX(p) / MAX_Y == 0) ? true : false; }
inline bool IS_RIGHT_BORDER(Point p) { return ( INDEX(p) % MAX_X == MAX_X - 1) ? true : false; }
inline bool IS_LEFT_BORDER(Point p) { return ( INDEX(p) % MAX_X == 0) ? true : false; }

inline int REVERSE_INDEX_X(int num) { return ((int) num % MAX_X); }
inline int REVERSE_INDEX_Y(int num) { return ((int) num / MAX_Y); }

double DISTANCE(int num1, int num2);


typedef set< pair<RP::Point,double> > ASet; //ASet is set of pairs of values. Each pair has pair of coordinates (x,y), representing the position of the squares from the environment matriz and the other is a 

class Pathplan
{
	protected:

		list<state> pathFull;  //full solution, showing possible partial branches
		list<state> pathFinal; //final solution, for path execution purposes

		//----- Sets -----
		ASet Closed;
		ASet Open;

		Grid env[MAX_X][MAX_Y]; //environment matrix
		int backpointer[MAX_X * MAX_Y]; //stores the path from the goal to the start

		////----- Matrixes -----
		double g_score[MAX_X][MAX_Y];
		double h_score[MAX_X][MAX_Y];
		double f_score[MAX_X][MAX_Y];
		int cost[MAX_X][MAX_Y];
		
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
		
		//returns a specific node on pathFinal (initialState is 0)		
		Point getPathNode(int nodeIndex); 
		
		void runPathplan( int pathplanIndex=PATHPLAN_RRT );		

		//fills the enviroment with positions of the obstacles (currently, only for players)
		void fillEnv(vector<Point> playersPositions); 
		
		bool aStar(RP::Point start, RP::Point goal);
		inline void setBackpointer(int index, int value) { backpointer[index] = value; }
		inline int getBackpointer(int index) { return backpointer[index]; }
		void print();
};


#endif
