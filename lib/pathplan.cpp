#ifndef _PATHPLAN_CPP_
#define _PATHPLAN_CPP_

#include <iostream>

#include "pathplan.h"
#include "point.h"

using RP::Point;
using namespace std;

Pathplan::Pathplan(Point initial, Point final)
{
	this->initialpos = initial;
	this->finalpos = final;
}

Pathplan::Pathplan()
{
	this->initialpos = Point(0.0, 0.0);
	this->finalpos = Point(0.0, 0.0);
}

Pathplan::~Pathplan()
{
}

void Pathplan::fillEnv_playerBox(int x, int y, int safetyCells)
{
	const int side = safetyCells; //MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;
			
	for(int i=0; i<side; i++)
		for(int k=0; k<side; k++)
			env[x+i][y+k] = OBSTACLE;
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
            switch (env[i][j]){
                case FREE: cout << " "; break;
                case MARKER: cout << "X"; break;
                case OBSTACLE: cout << "#"; break;
                case NODE: cout << "."; break;
                case PATH: cout << "o"; break;
			}
			cout << endl;
		}
    }	

}

void Pathplan::fillEnv(vector<Point> playersPositions)
{
	int centerx, centery;
	int nSafetyCells = 2;

	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			env[x][y] = FREE;

	vector<Point>::iterator it;
	for(it=playersPositions.begin(); it<playersPositions.end(); it++)
	{
		centerx = round( MM_TO_CELLS((*it).getX()) );
		centery = round( MM_TO_CELLS((*it).getY()) );
		fillEnv_playerBox(centerx,centery,nSafetyCells);
	}
}

Point Pathplan::getPathNode(int nodeIndex)
{
	list<Point>::iterator it;

	for( it=pathFull.begin(); nodeIndex>0; it++ )
		nodeIndex--;

	Point node = *it;
	
	node.setX(CELLS_TO_MM(node.getX()));
	node.setY(CELLS_TO_MM(node.getY()));
	
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
