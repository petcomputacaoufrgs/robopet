#ifndef __ROBOPET_PATHPLAN_H__
#define __ROBOPET_PATHPLAN_H__

#include <vector>
#include "point.h"
#include "constants.h"
#include "rrt.h"
#include <iostream>
#include <set>
#include <cmath>
#include <cstdio>

using namespace std;

#ifndef _GRID_H_
#define _GRID_H_
#define GRID_SIZE_X 5
#define GRID_SIZE_Y 5

enum flags
{
    OPEN_BIT = 1,
    NEW_BIT = 2
};

typedef unsigned char byte;
typedef int Grid;

#if 0
class Grid
{
    private:
        byte tags; //Flags enumeradas acima

        byte sizeX; //tamanho da grade, para o sistema do RoboPET
        byte sizeY;

    public:
        Grid(int sx = GRID_SIZE_X, int sy = GRID_SIZE_Y);
        ~Grid(){ };

        inline bool isOpen(){    return (tags & OPEN_BIT) && !(tags & NEW_BIT);    }  //está pronto para ser analisado
        inline bool isClosed(){    return !(tags & OPEN_BIT) && !(tags & NEW_BIT);    } //já analisado
        inline bool isNew(){    return (tags & NEW_BIT);    } //

        inline void setOpen(){    tags = (tags | OPEN_BIT) - (tags & NEW_BIT);    }
        inline void setClosed(){    tags = tags - (tags & OPEN_BIT) - (tags & NEW_BIT);    }

        //inline void setCost(byte newCost){    cost = newCost;    }
        //inline byte getCost(){    return cost;    }

};
#endif

#endif

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

inline bool IS_BOTTOM_BORDER(int num) { return ((int) num / MAX_Y == MAX_Y - 1) ? true : false; }
inline bool IS_UPPER_BORDER(int num) { return ((int) num / MAX_Y == 0) ? true : false; }
inline bool IS_RIGHT_BORDER(int num) { return ((int) num % MAX_X == MAX_X - 1) ? true : false; }
inline bool IS_LEFT_BORDER(int num) { return ((int) num % MAX_X == 0) ? true : false; }

inline int INDEX(int x, int y) { return x + (y * MAX_X); }
inline int REVERSE_INDEX_X(int num) { return ((int) num % MAX_X); }
inline int REVERSE_INDEX_Y(int num) { return ((int) num / MAX_Y); }

double DISTANCE(int num1, int num2);


typedef set< pair<RP::Point,double> > ASet;

class Pathplan
{
	protected:
		list<state> pathFull;  //full solution, showing possible partial branches
		list<state> pathFinal; //final solution, for path execution purposes

		ASet Closed;
		ASet Open;

		Grid env[MAX_X][MAX_Y]; //environment matrix
		int backpointer[MAX_X][MAX_Y];
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
				
		Point getPathNode(int nodeIndex); //returns a specific node on pathFinal (initialState is 0)
		
		void runPathplan( int pathplanIndex=PATHPLAN_RRT );		
		void fillEnv(vector<Point> playersPositions); //fills the enviroment with positions of the obstacles (currently, only for players)
		
		bool aStar(RP::Point start, RP::Point goal);
		
		//inline void setBackpointer(int index, int value) { backpointer[index] = value; }
		//inline int getBackpointer(int index) { return backpointer[index]; }
};


#endif
