#ifndef _ASTAR_CPP_
#define _ASTAR_CPP_

#include <cstdlib>
#include <cmath>
#include <cstring>
#include "astar.h"

using namespace std;

//Constructor
AStar::AStar()
{
		for(int i = 0; i < MAX_X; i++)
			for(int j = 0; j < MAX_Y; j++)
			{
				g_score[i][j] = 0;
				h_score[i][j] = 0;
				f_score[i][j] = 0;
				cost[i][j] = 0;
				backpointer[i*MAX_X + j] = -1;
			}
}

//Destructor
AStar::~AStar()
{	
}

//Runs the AStar algorithm
bool AStar::aStarPlan(Grid env[][MAX_Y], RP::Point start, RP::Point goal, int costAStar[][MAX_Y])
{
		using RP::Point;
	
		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
				cost[i][j] = costAStar[i][j];	

		//'Close' and 'Open' are ASet objects. Each of its terms has a point and a double variable
		Closed.clear();
		Open.clear();
		Open.insert( make_pair(0, start) );

		//an obstacle has the value 1000. E.g. cost[x][y] = 1000;

		cost[6][6] = 1000;

		//h_score: heuristics (a guess about the distance from a square to the goal) - this heuristics calculates the distance between two squares (points) on the environment matrix using euclidean distance [sqrt((x-x0)²+(y-y0)²)]
		//g_score: cost to go from a parent square to a son square
		//f_score: h_score + g_score

		int x = (int)start.getX();
		int y = (int)start.getY();
		g_score[x][y] = 0;
		h_score[x][y] = start.getDistance(goal);
		f_score[x][y] = g_score[x][y] + h_score[x][y];

		//Sets the distance from each square of environment matriz to the goal square
		for(int i = 0; i < MAX_X; i++)
			for(int j = 0; j < MAX_Y; j++)
			{
				Point aux(i,j);
				h_score[i][j] = aux.getDistance(goal);
			}

		//RIGHT, LEFT, DOWN, UP, RIGHT_DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN
		Point corners[] = { Point(1,0), Point(-1,0), Point(0,1),
							Point(0,-1), Point(1,1), Point(-1,-1),
							Point(1,-1), Point(-1,1) };

		while(!Open.empty())
		{
		    ASet::iterator a = Open.begin(); //the iterator points to the first item in the set 'Open'
			Point p = a->second; //the point p now has the first element of the pair pointed by the a iterator
			if( p == goal)
				 return true; //the goal has been reached, finishes AStar algorithm

			//we analized the point p. It has to be set as closed, should be placed in the 'Closed' set and erased from the 'Open' one
			env[(int)p.getX()][(int)p.getY()].setClosed();
			Closed.insert(*a);
			Open.erase(*a);

			for(int i = 0; i < 8; i++) //8 == number of neighbors
			{
				Point neighbor = p + corners[i];

				if( (IS_BOTTOM_BORDER(p) && (i == DOWN || i == LEFT_DOWN || i == RIGHT_DOWN)) ||
				   (IS_UPPER_BORDER(p) && (i == UP || i == LEFT_UP || i == RIGHT_UP)) ||
				   (IS_RIGHT_BORDER(p) && (i == RIGHT || i == RIGHT_UP || i == RIGHT_DOWN)) ||
				   (IS_LEFT_BORDER(p) && (i == LEFT || i == LEFT_UP || i == LEFT_DOWN)) )
				  continue;

			   	bool podePassar = true;
		       	for(int j = 0; j < 4; j++)
					{
						Point coords = p + corners[j];
		               	if(cost[(int)coords.getX()][(int)coords.getY()] == 1000)
		               	{
		                	podePassar = false;
		                   	break;
		               	}
					}

		       	if(!podePassar)
		          	continue; //termina a iteração vigente do for e começa outra

				if(env[(int)neighbor.getX()][(int)neighbor.getY()].isClosed())
				  	continue; //goes to another iteration in the loop 'for'

			   	double tentative_g_score = 	g_score[(int)p.getX()][(int)p.getY()] +
										   	p.getDistance(neighbor);

			   	bool tentative_is_better = false;
			   	if(env[(int)neighbor.getX()][(int)neighbor.getY()].isNew())
			   	{
				   env[(int)neighbor.getX()][(int)neighbor.getY()].setOpen();
				   tentative_is_better = true;
			   	}
			   	else if(tentative_g_score < g_score[(int)neighbor.getX()][(int)neighbor.getY()])
				   tentative_is_better = true;

			   	if(tentative_is_better) //se a posição for a melhor, então ela é armazenada
			   	{   					   //no vetor backpointer
				   setBackpointer(INDEX(neighbor), INDEX(p));
				   int x = (int)neighbor.getX();
				   int y = (int)neighbor.getY();
				   g_score[x][y] = tentative_g_score;
				   f_score[x][y] = g_score[x][y] + h_score[x][y] + cost[x][y];
				   Open.insert( make_pair(f_score[x][y],neighbor) );
			   	}
			}
		}

		return false;
}

//Runs the AStar algorithm and returns the next point in the field to visit to reach the goal
Point AStar::nextNode(Grid envAStar[][MAX_Y], RP::Point start, RP::Point goal, int costAStar[][MAX_Y])
{
		if (aStarPlan(envAStar,start,goal,costAStar))
		{
			int i, j;
			cout << endl << "===================" << endl;

			i = INDEX(goal);
			while(i != INDEX(start))
			{
				cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;
				j = i;
				i = getBackpointer(i); //pega o próximo nodo do caminho de goal até start
			}
			cout << REVERSE_INDEX_X(i) << ", " << REVERSE_INDEX_Y(i) << endl;
			Point p(REVERSE_INDEX_X(j),REVERSE_INDEX_Y(j));

			cout << endl << "===================" << endl;
			printAStar();
			cout << endl << "===================" << endl;
			return p;			
		}
		else
		{
			cout << "Can't reach destination" << endl;
			Point q(0.0, 0.0);
			return q;
		}
}


//prints the results of the AStar algorithm
void AStar::printAStar()
{
	    //backpointer é um vetor com o tamanho do campo
		char mask[] = "RLDU3791";
		Point corners[] = { Point(1,0), Point(-1,0), Point(0,1),
							Point(0,-1), Point(1,1), Point(-1,-1),
							Point(1,-1), Point(-1,1) };
        for(int i=0; i<MAX_X; i++)
            cout << i%10 << " ";
        cout << endl << endl;
		for(int j = 0; j < MAX_Y; j++)
		{
		   for(int i = 0; i < MAX_X; i++)
		   {
			  Point pos = Point(i,j);
			  for(int k = 0; k < 8; k++)
			  {
				  if(cost[(int)pos.getX()][(int)pos.getY()] == 1000)
				  {
					  cout << "#" << " ";
					  break;
				  }
				  Point test = pos + corners[k];
				  if(backpointer[INDEX(pos)] == -1)
				  {
					  cout << "_" << " ";
					  break;
				  }
				  else if(INDEX(test) == backpointer[INDEX(pos)])
				  {
					  cout << mask[k] << " ";
				  }
			  }
		   }
		   cout << endl;
		}
		cout << endl << "===================" << endl;
}

#endif
