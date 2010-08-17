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
		
#if 0		
		Point start(2.0, 2.0);
		//cout << "1" << endl;
		Point goal(10.0, 10.0);
		//cout << "2" << endl; 

		int i; 
	
		campo.aStar(start, goal);
		//cout << "3" << endl;
    	cout << endl << "===================" << endl;
		
		i = INDEX(goal); //(int)goal.getIndex();

		while(i != INDEX(start))
		{
			cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;
			i = campo.getBackpointer(i); //pega o próximo nodo do caminho de goal até start
			//cout << "i: " << i << endl;
		}
		cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;

		cout << endl << "===================" << endl;
		campo.print();
		cout << endl << "===================" << endl;	
#endif	
}
