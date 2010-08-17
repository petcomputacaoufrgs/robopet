/*#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
	Vector p1(1,0), p2(4,3);

}
*/

#include "pathplan.h"
#include "vector.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
		Pathplan campo;

		Point start(2.0, 2.0);
		Point goal(7.0, 7.0);

		int i;

		campo.aStar(start, goal);
    	cout << endl << "===================" << endl;

		i = INDEX(goal);

		while(i != INDEX(start))
		{
			cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;
			i = campo.getBackpointer(i); //pega o próximo nodo do caminho de goal até start
			cout << "i: " << i << endl;
		}
		cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;

		cout << endl << "===================" << endl;
		campo.print();
		cout << endl << "===================" << endl;
}
