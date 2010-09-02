#ifndef _PATHPLAN_CPP_
#define _PATHPLAN_CPP_

#include <iostream>
#include "pathplan.h"

using namespace std;

Pathplan::Pathplan(Point initial, Point final)
{
	this->initialpos = initial;
	this->finalpos = final;
	for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
				costAStar[x][y] = 0;
}

Pathplan::Pathplan()
{
	Point initial(0.0, 0.0);
	Point final(0.0, 0.0);
	this->initialpos = initial;
	this->finalpos = final;
	for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
				costAStar[x][y] = 0;
}

Pathplan::~Pathplan()
{
}

void Pathplan::runPathplan( int pathplanIndex )
{
	switch(pathplanIndex)
	{
		case PATHPLAN_RRT:
			runRRT();
			break;

		case PATHPLAN_ASTAR:
			runAStar();
			break;
	}
}

void Pathplan::runRRT()
/* interface for Cristiano's RRT implementation */
{
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	state goal = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;

    RRTTree *solutionTree;
	solutionTree = RRTPlan(envRRT,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);
	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
}


void Pathplan::runAStar()
{
	//me explica esses MM_to_cells cristiano (by joão gross)
	state initial = state( (int) MM_TO_CELLS( initialpos.getX() ), (int) MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( (int) MM_TO_CELLS( finalpos.getX() ), (int) MM_TO_CELLS( finalpos.getY() )) ;

	//cout << initial.getX() << " " << initial.getY() << endl;
	//cout << goal.getX() << " " << goal.getY() << endl;

	AStar astar;
	//state path(astar.nextNode(envAStar, initial, goal, costAStar));
	if (INDEX(initial) < 0 || initial.getX() > (MAX_X-1) || initial.getY() > (MAX_Y-1) || INDEX(goal) < 0 || goal.getX() > (MAX_X-1) || goal.getY() > (MAX_Y-1))
	{
		cout << "Points out of range!" << endl;
		return;		
	}

	state path(astar.nextNode(envAStar, initial, goal, costAStar));
	pathFinal.push_front(path);

	Point p = pathFinal.front();
	if (INDEX(p))
	{
		//cout << "Next Point: " << p.getX() << ", " << p.getY() << endl;
		//cout << "Full path: " << endl;
		for (list<Point>::iterator a = astar.pathFullAStarBegin(); 
			 a != astar.pathFullAStarEnd(); a++)
		{
			pathFull.push_back(*a);
			//cout <<	a->getX() << "," << a->getY() << endl;
		}
	}
}


void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{
	const int lado = 2; //MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;
	//printf("%i\n",lado);
		
	for(int i=0; i<lado; i++)
		for(int k=0; k<lado; k++)
		{
			envRRT[x+i][y+k] = OBSTACULO;
			costAStar[x+i][y+k] = 1000;
		}
}


void Pathplan::fillEnv(vector<Point> playersPositions)
{
	int centerx, centery;
	int nSafetyCells = 0;

	for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
		{
			envRRT[x][y] = LIVRE;
			costAStar[x][y] = LIVRE;
		}

	vector<Point>::iterator it;
	for(it=playersPositions.begin(); it<playersPositions.end(); it++)
	{
		centerx = (int)MM_TO_CELLS((*it).getX());
		centery = (int)MM_TO_CELLS((*it).getY());
		fillEnv_playerBox(centerx,centery,nSafetyCells);
	}

}

Point Pathplan::getPathNode(int nodeIndex)
{
	list<state>::iterator it;
	for( it=pathFinal.begin(); nodeIndex>0; it++ )
		nodeIndex--;

	return *it;
}

#endif
