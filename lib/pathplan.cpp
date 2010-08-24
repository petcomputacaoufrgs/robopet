#ifndef _PATHPLAN_CPP_
#define _PATHPLAN_CPP_

#include <iostream>
#include "pathplan.h"

using namespace std;

Pathplan::Pathplan(Point initialpos, Point finalpos)
{
	this->initialpos = initialpos;
	this->finalpos = finalpos;
	for (int y = 0; y < MAX_X; y++)
			for (int x = 0; x < MAX_Y; x++)
				costAStar[x][y] = 0;
}

Pathplan::Pathplan()
{
	Point initial(0.0, 0.0);
	Point final(0.0, 0.0);
	this->initialpos = initial;
	this->finalpos = final;
	for (int y = 0; y < MAX_X; y++)
			for (int x = 0; x < MAX_Y; x++)
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
{
	//this is the interface for Cristiano's RRT implementation
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	//cout << "initial: " << initialpos.getX() << ", " << initialpos.getY() << endl;
	//cout << "initial mm: " << initial.getX() << ", " << initial.getY() << endl;
	state goal = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;
	//cout << "final: " << finalpos.getX() << ", " << finalpos.getY() << endl;
	//cout << "final mm: " << goal.getX() << ", " << goal.getY() << endl;

    RRTTree *solutionTree;
	solutionTree = RRTPlan(envRRT,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);
	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
}


void Pathplan::runAStar()
{
	state initial = state( (int) MM_TO_CELLS( initialpos.getX() ), (int) MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( (int) MM_TO_CELLS( finalpos.getX() ), (int) MM_TO_CELLS( finalpos.getY() )) ;

	AStar astar;
	//state path(astar.nextNode(envAStar, initial, goal, costAStar));
	state path(astar.nextNode(envAStar, initialpos, finalpos, costAStar));
	//state path(astar.nextNode(envAStar, initialpos, finalpos, costAStar));
	pathFinal.push_front(path);

	Point p = pathFinal.front();
	cout << "Next Point: " << p.getX() << ", " << p.getY() << endl;

	for (list<Point>::iterator a = astar.pathFullAStarBegin(); a != astar.pathFullAStarEnd(); a++)
	{
		pathFull.push_back(*a);
		cout <<	a->getX() << "," << a->getY() << endl;
	}
}


void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{
	const int lado = MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;

	for(int i=0; i<lado; i++)
        for(int k=0; k<lado; k++)
		{
            envRRT[x+i - lado/2][y+k - lado/2] = OBSTACULO;
			costAStar[x+i - lado/2][y+k - lado/2] = 1000;
		}
}


void Pathplan::fillEnv(vector<Point> playersPositions)
{
	int centerx, centery;
	int nSafetyCells = 4;

	for(int i=0;i<MAX_X;i++)
		for(int j=0;j<MAX_Y;j++)
		{
			envRRT[i][j] = LIVRE;
			costAStar[i][j] = LIVRE;
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
