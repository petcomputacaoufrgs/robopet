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
		Point start(2.0,2.0);
		Point goal(12.0,12.0);
		Pathplan field(start, goal);
		cout << "Runnig AStar" << endl;
		field.runPathplan(PATHPLAN_ASTAR);
		
		cout << "Runnig RRT" << endl;
		field.runPathplan(PATHPLAN_RRT);
#endif 
			
/*			
		{
			
			Point start(12.0, 12.0);
			Point goal(2.0, 2.0);
			Point nextp;
			nextp = campo.nextNode(start, goal);
			cout << "Pont received: " << nextp.getX() << ", " << nextp.getY() << endl;
		}
*/		

}
