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
	cout << "Peitos: " << initialpos.getX() << "," << initialpos.getY() << " | " << finalpos.getX() << "," << finalpos.getY() << endl;
	state initial = initialpos;
	state goal    = finalpos;

	if(initial.getX() == goal.getX() && initial.getY() == goal.getY()) {
		pathFinal.push_front(initial);
		pathFinal.push_front(goal);
		cout << "Trague-o: " << initial.getX() << "," << initial.getY() << " | " << goal.getX() << "," << goal.getY() << endl;
		return;
	}

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
	//path.setX( CELLS_TO_MM(path.getX() ) );
    	//path.setY( CELLS_TO_MM( path.getY() ) );	
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

	//astar.printAStar();
}


void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{
	const int lado = safetyCells; //MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;
	//printf("%i\n",lado);
		
	for(int i=0; i<lado; i++)
		for(int k=0; k<lado; k++)
		{
			envRRT[x+i][y+k] = OBSTACULO;
			costAStar[x+i][y+k] = 1000;
		}
}

char toChar(int cost)
{
	if (cost == 1000)
		return 'x';
	else
		return 'o';
}

void Pathplan::printEnv()
{
	for (unsigned int i = 0; i < MAX_Y; i += 1)
	{
		for (unsigned int j = 0; j < MAX_X; j += 1)
		{
			cout << toChar(costAStar[j][i]) << " ";
		}
		cout << endl;
	}

}

void Pathplan::fillEnv(vector<Point> playersPositions)
{
	int centerx, centery;
	int nSafetyCells = 1;

	for (int x = 0; x < MAX_X; x++)
			for (int y = 0; y < MAX_Y; y++)
		{
			envRRT[x][y] = LIVRE;
			costAStar[x][y] = LIVRE;
		}

	vector<Point>::iterator it;
	for(it=playersPositions.begin(); it<playersPositions.end(); it++)
	{
		centerx = round( MM_TO_CELLS((*it).getX()) );
		centery = round( MM_TO_CELLS((*it).getY()) );
		fillEnv_playerBox(centerx,centery,nSafetyCells);
	}

	printEnv();
}

Point Pathplan::getPathNode(int nodeIndex)
{
	list<state>::iterator it;

	for( it=pathFinal.begin(); nodeIndex>0; it++ )
		nodeIndex--;

	state node = *it;
	node.setX(CELLS_TO_MM(node.getX()));
	node.setY(CELLS_TO_MM(node.getY()));
	cout << "Huevos: " << node.getX() << "," << node.getY() << endl;
	return node;
}

void Pathplan::setInitialPos(Point pos)
{
	initialpos = Point( round(MM_TO_CELLS( pos.getX() )), round(MM_TO_CELLS( pos.getY() )) );
}

void Pathplan::setFinalPos(Point pos)
{
	finalpos = Point( round(MM_TO_CELLS( pos.getX() )), round(MM_TO_CELLS( pos.getY() )) );
}

#endif
