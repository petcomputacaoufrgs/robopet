#ifndef _PATHPLAN_CPP_
#define _PATHPLAN_CPP_

#include <iostream>

#include "pathplan.h"
#include "point.h"

using RP::Point;
using namespace std;

Pathplan::Pathplan(Node initial, Node final)
{
	this->initialpos = initial;
	this->finalpos = final;
	this->radius = OBSTACULE_RADIUS;
}

Pathplan::Pathplan()
{
	this->initialpos = Node(0.0, 0.0);
	this->finalpos = Node(0.0, 0.0);
	this->radius = OBSTACULE_RADIUS;
}

Pathplan::~Pathplan()
{
}

void Pathplan::fillEnv_playerBox(int x, int y)
{
	
	const int side = 2*(this->getRadius()); //MM_TO_CELLS( ROBOT_RADIUS_MM ) + safetyCells;
			
	for(int i=0; i<side; i++)
		for(int k=0; k<side; k++)
		{
			int newx = x+i-side/2,
				newy = y+k-side/2;
				
			if( Point(x,y).getDistance(Point(newx,newy)) < this->getRadius() &&
				newx>=0 && newx<MAX_X &&
				newy>=0 && newy<MAX_Y )
				
				env[newx][newy] = OBSTACLE;
		}
}

int Pathplan::getRadius()
{
	return radius;
}

void Pathplan::setRadius(int radius)
{
	this->radius = radius;
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

void Pathplan::fillEnv(vector<Point> positions)
{
	int centerx, centery;

	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			env[x][y] = FREE;

	vector<Point>::iterator it;
	for(it=positions.begin(); it<positions.end(); it++)
	{
		centerx = round( MM_TO_CELLS_X((*it).getX()) );
		centery = round( MM_TO_CELLS_Y((*it).getY()) );
		fillEnv_playerBox(centerx,centery);
	}
}

Point Pathplan::getPathNode(int nodeIndex)
{
	list<Node>::iterator it;

	for( it=pathFull.begin(); nodeIndex>0; it++ )
		nodeIndex--;

	Node node = *it;
	
	node.setX(CELLS_TO_MM_X(node.getX()));
	node.setY(CELLS_TO_MM_Y(node.getY()));
	
	return Point(node.getX(), node.getY());
}

void Pathplan::setInitialPos(Node pos)
{
	initialpos = Node( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

void Pathplan::setFinalPos(Node pos)
{
	finalpos = Node( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

void Pathplan::setInitialPos(Point pos)
{
	initialpos = Node( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

void Pathplan::setFinalPos(Point pos)
{
	finalpos = Node( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

#endif
