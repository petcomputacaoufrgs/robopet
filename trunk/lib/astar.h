#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <iostream>
#include <set>
#include <list>
#include "point.h"
#include "grid.h"
#include "constants.h"

//RLDU3791

using namespace std;

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
inline int INDEX(int x, int y) { return x + (y * MAX_X); } //y: colums, x: lines
inline bool IS_BOTTOM_BORDER(Point p) { return ( INDEX(p) / MAX_Y == (MAX_Y - 1)) ? true : false; }
inline bool IS_UPPER_BORDER(Point p) { return ( INDEX(p) / MAX_Y == 0) ? true : false; }
inline bool IS_RIGHT_BORDER(Point p) { return ( INDEX(p) % MAX_X == (MAX_X - 1)) ? true : false; }
inline bool IS_LEFT_BORDER(Point p) { return ( INDEX(p) % MAX_X == 0) ? true : false; }

inline int REVERSE_INDEX_X(int num) { return ((int) num / MAX_X); }
inline int REVERSE_INDEX_Y(int num) { return ((int) num - (num / MAX_X)*MAX_X ); }

double DISTANCE(int num1, int num2);

//typedef set< pair<double,RP::Point> > ASet; //ASet is set of pairs of values. Each pair has pair of coordinates (x,y), representing the position of the squares from the environment matriz and the other is a

class Par
{
	private:
      RP::Point p;
      double cost;

	public:
	  Par() {  }
	  Par(RP::Point element, double c = 0) { p = element; cost = c; }
	  ~Par() { }

	  bool operator<(const Par& other) const;
	  inline Point getPoint() const { return p; }
	  inline double getCost() const { return cost; }
};

class AStar
{
	protected:

		//---- Matrixes ----
		double g_score[MAX_X][MAX_Y];
		double h_score[MAX_X][MAX_Y];
		double f_score[MAX_X][MAX_Y];
		int cost[MAX_X][MAX_Y];
		int backpointer[MAX_X * MAX_Y]; //stores the path from the goal to the start

		//---- Total path ----
		list<Point> pathFullAStar;

		//----- Sets -----
		set<Par> Closed;
		set<Par> Open;

		//---- Functions ----
		void printAStar();
		bool aStarPlan(Grid envAStar[MAX_X][MAX_Y], RP::Point start, RP::Point goal, int costAStar[MAX_X][MAX_Y]); //executes the Astar algorithm

	public:

		//---- Constructor and Destructor ----
		AStar();
		~AStar();

		//---- Functions ----
		Point nextNode(Grid envAStar[MAX_X][MAX_Y], RP::Point start, RP::Point goal, int costAStar[MAX_X][MAX_Y]);
		list<Point>::iterator pathFullAStarBegin() { return pathFullAStar.begin(); }
		list<Point>::iterator pathFullAStarEnd() { return pathFullAStar.end(); }

		//---- Inline Functions ----
		inline void setBackpointer(int index, int value) { backpointer[index] = value; }
		inline int getBackpointer(int index) { return backpointer[index]; }
};

#endif
