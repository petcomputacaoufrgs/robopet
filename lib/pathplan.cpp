#ifndef _PATHPLAN_CPP_
#define _PATHPLAN_CPP_

#include <iostream>
#include "pathplan.h"

using namespace std;

Pathplan::Pathplan(Point initialpos, Point finalpos)
{
	this->initialpos = initialpos;
	this->finalpos = finalpos;
}

Pathplan::Pathplan()
{
	Point initial(0.0, 0.0);
	Point final(0.0, 0.0);
	this->initialpos = initial;
	this->finalpos = final;	
}

Pathplan::~Pathplan()
{
}

void Pathplan::runRRT()
{
	//this is the interface for Cristiano's RRT implementation
	state initial = state( MM_TO_CELLS( initialpos.getX() ), MM_TO_CELLS( initialpos.getY() ));
	state goal    = state( MM_TO_CELLS( finalpos.getX() ), MM_TO_CELLS( finalpos.getY() )) ;

    RRTTree *solutionTree;
	solutionTree = RRTPlan(envRRT,initial,goal);

    this->pathFull = solutionTree->treeToList();
	this->pathFinal = solutionTree->findSolucao(goal);

	//print(solutionTree,initial,goal,caminhoSolucao,env); //imprime resultado no console
}


void Pathplan::runAStar()
{	
	AStar astar;	
	Point p = astar.nextNode(envAStar, initialpos, finalpos, costAStar);
	cout << "Next Point: " << p.getX() << ", " << p.getY() << endl;
}


void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{
	const int lado = MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;

	for(int i=0; i<lado; i++)
        for(int k=0; k<lado; k++)
		{
            envRRT[x+i - lado/2][y+k - lado/2] = OBSTACULO;
			costAStar[x+i - lado/2][y+k - lado/2] = OBSTACULO;
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

#endif



