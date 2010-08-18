#include "pathplan.h"
#include "vector.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
		{
			Pathplan campo;
			Point start(12.0, 12.0);
			Point goal(2.0, 2.0);
			Point nextp;
			nextp = campo.nextNode(start, goal);
			cout << "Pont received: " << nextp.getX() << ", " << nextp.getY() << endl;
		}
		{
			Pathplan campo;
			Point start(2.0, 2.0);
			Point goal(12.0, 12.0);
			Point nextp;
			nextp = campo.nextNode(start, goal);
			cout << "Pont received: " << nextp.getX() << ", " << nextp.getY() << endl;
		}
		{
			Pathplan campo;
			Point start(10.0, 0.0);
			Point goal(5.0, 3.0);
			Point nextp;
			nextp = campo.nextNode(start, goal);
			cout << "Pont received: " << nextp.getX() << ", " << nextp.getY() << endl;
		}

}
