#include "pathplan.h"
#include "vector.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

//runPathplan(PATHPLAN_ASTAR)

int main()
{
		Point start(2.0,2.0);
		Point goal(4.0,4.0);
		Pathplan field(start, goal);
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
		
		//cout << "Runnig RRT" << endl;
		//field.runPathplan(PATHPLAN_RRT);
}
