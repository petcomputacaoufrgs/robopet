#ifndef _ASTAR_CPP_
#define _ASTAR_CPP_

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <list>
#include "astar.h"
#include <cstdio>

using namespace std;

/*
Info:
	h_score: heuristics (a guess about the distance from a square to the goal) - this heuristics calculates the distance between two squares (points) on the environment matrix using euclidean distance [sqrt((x-x0)²+(y-y0)²)]
	g_score: cost to go from a parent square to a son square
	f_score: h_score + g_score
*/

bool Par::operator<(const Par& other) const
{
    return cost < other.cost;
}

//Constructor
AStar::AStar()
{
		//x: linhas, y: colunas
		for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
			{
				g_score[x][y] = 0;
				h_score[x][y] = 0;
				f_score[x][y] = 0;
				//cost[i][j] = 0; já é inicializado no aStarPlan
				backpointer[INDEX(x,y)] = -1;
			}
}

//Destructor
AStar::~AStar()
{
}

//Runs the AStar algorithm
bool AStar::aStarPlan(Grid env[MAX_X][MAX_Y], RP::Point start, RP::Point goal, int costAStar[MAX_X][MAX_Y])
{
		using RP::Point;

		//---- Closed and Open are ASet variables from class astar ----
		Open.clear();
		Closed.clear();
		Open.insert(Par(start,0));	

		for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
				cost[x][y] = costAStar[x][y];

		//cost[6][6] = 1000;

		int x = (int)start.getX();
		int y = (int)start.getY();
		g_score[x][y] = 0;
		h_score[x][y] = start.getDistance(goal);
		f_score[x][y] = g_score[x][y] + h_score[x][y];

		//Sets the distance from each square of environment matriz to the goal square
		for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
			{
				Point aux(x,y);
				h_score[x][y] = aux.getDistance(goal);
				//cout << INDEX(x,y) << " - " << h_score[x][y] << endl;
			}

		//RIGHT, LEFT, DOWN, UP, RIGHT_DOWN, LEFT_UP, RIGHT_UP, LEFT_DOWN
		Point corners[] = { Point(1,0), Point(-1,0), Point(0,1),
							Point(0,-1), Point(1,1), Point(-1,-1),
							Point(1,-1), Point(-1,1) };

		while(!Open.empty())
		{
		    set<Par>::iterator a = Open.begin(); //the iterator points to the first item in the set 'Open'
			Point p = a->getPoint(); //the point p now has the first element of the pair pointed by the a iterator
			if( p == goal)
				 return true; //the goal has been reached, finishes AStar algorithm

			//---- p is set as closed, because we already visited him ----
			env[(int)p.getX()][(int)p.getY()].setClosed();
			Closed.insert(*a);
			Open.erase(*a);

			for(int i = 0; i < 8; i++) //8 == number of neighbors
			{
				Point neighbor = p + corners[i];
				if((IS_BOTTOM_BORDER(p) && (i == DOWN || i == LEFT_DOWN || i == RIGHT_DOWN)) ||
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
				   Open.insert( Par(neighbor,f_score[x][y]) );
			   	}

			}
		}

		return false;
}

//Runs the AStar algorithm and returns the next point in the field to visit to reach the goal
Point AStar::nextNode(Grid envAStar[MAX_X][MAX_Y], RP::Point start, RP::Point goal, int costAStar[MAX_X][MAX_Y])
{
		if (start == goal)
			return goal;		

		if (aStarPlan(envAStar,start,goal,costAStar))
		{
			int i, j;
			i = INDEX(goal);
			Point p(REVERSE_INDEX_X(i),REVERSE_INDEX_Y(i));
			pathFullAStar.push_front(p);

			while(i != INDEX(start))
			{
				j = i;
				i = getBackpointer(i); //pega o próximo nodo do caminho de goal até start
				p.setXY(REVERSE_INDEX_X(i),REVERSE_INDEX_Y(i));
				//cout << p.getX() << "," << p.getY() << endl;
				pathFullAStar.push_front(p);
			}
			p.setXY(REVERSE_INDEX_X(j),REVERSE_INDEX_Y(j));
			printAStar(); //comment this
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
		cout << "===============================" << endl;
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
