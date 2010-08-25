#include "pathplan.h"
#include "vector.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

//runPathplan(PATHPLAN_ASTAR)

int main()
{
	#if 0
	cout << "MAX_X: 0 to " << MAX_X-1 << ", MAX_Y: 0 to " << MAX_Y-1 << endl << endl;	
	{
		Point start(0.0,2.0);
		Point goal(8.0,19.0);
		Pathplan field(start, goal);
		cout << "Start: " << start.getX() << "," << start.getY() << endl;
		cout << "Goal: " << goal.getX() << "," << goal.getY() << endl;
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
	}
	getchar();
	{
		Point start(0.0,0.0);
		Point goal(0.0,0.0);
		Pathplan field(start, goal);
		cout << "Start: " << start.getX() << "," << start.getY() << endl;
		cout << "Goal: " << goal.getX() << "," << goal.getY() << endl;
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
	}
	getchar();
	{
		Point start(0.0,0.0);
		Point goal(19.0,19.0);
		Pathplan field(start, goal);
		cout << "Start: " << start.getX() << "," << start.getY() << endl;
		cout << "Goal: " << goal.getX() << "," << goal.getY() << endl;
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
	}
	getchar();
	{
		Point start(12.0,2.0);
		Point goal(4.0,23.0);
		Pathplan field(start, goal);
		cout << "Start: " << start.getX() << "," << start.getY() << endl;
		cout << "Goal: " << goal.getX() << "," << goal.getY() << endl;
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
	}
	getchar();
	{
		Point start(4.0,0.0);
		Point goal(8.0,12.0);
		Pathplan field(start, goal);
		cout << "Start: " << start.getX() << "," << start.getY() << endl;
		cout << "Goal: " << goal.getX() << "," << goal.getY() << endl;
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
	}
	#endif
		//cout << "Runnig RRT" << endl;
		//field.runPathplan(PATHPLAN_RRT);
}
