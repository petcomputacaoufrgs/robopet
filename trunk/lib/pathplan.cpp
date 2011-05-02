#include <iostream>
#include <stdlib.h>

#include "utils.h"

#include "pathplan.h"

using RP::Point;
using namespace std;

Pathplan::Pathplan(Point initial, Point final)
{
	this->initialpos = initial;
	this->finalpos = final;
	init();
}

Pathplan::Pathplan()
{
	this->initialpos = Point(0.0, 0.0);
	this->finalpos = Point(0.0, 0.0);
	init();
}

Pathplan::~Pathplan() {}

void Pathplan::init()
{
	this->radius = OBSTACULE_RADIUS;
	status = NOTHING;
	
	envMatrixX = ENV_MATRIX_SIZE_X;
	envMatrixY = (int)(envMatrixX * (FIELD_HEIGHT/(float)FIELD_WIDTH) + 1);
	
	env = (envType**) allocMatrix(envMatrixX,envMatrixY,sizeof(envType) );
	
	for (int i = 0; i < envMatrixX; i += 1)
		for (int j = 0; j < envMatrixY; j += 1)
            env[i][j] = FREE;
}


void Pathplan::fillEnv_playerBox(int x, int y)
{
	// Maybe this code could be optimized? It's a critical thing for pathplanning work smoothly.
	
	const int side = 2*(this->getRadius());
			
	for(int i=0; i<side; i++)
		for(int k=0; k<side; k++)
		{
			int newx = x+i-side/2,
				newy = y+k-side/2;
				
			if( Point(x,y).getDistance(Point(newx,newy)) < this->getRadius() &&
				newx>=0 && newx<envMatrixX &&
				newy>=0 && newy<envMatrixY )
				
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

void Pathplan::setEnvXY( int x, int y )
{
	envMatrixX = x;
	envMatrixY = y;
	
	free(env);
	env = (envType**) allocMatrix(envMatrixX,envMatrixY,sizeof(envType) );
}

int Pathplan::getEnvMatrixX()
{
	return envMatrixX;
}

int Pathplan::getEnvMatrixY()
{
	return envMatrixY;
}

void Pathplan::printEnv()
{
	for (int i = 0; i < envMatrixY; i += 1) {
		for (int j = 0; j < envMatrixX; j += 1) {
            switch (env[j][i]){
                case OBSTACLE: cout << "#"; break;
                default: cout << " "; break;
			}
		}
		cout << endl;
    }	
}

void Pathplan::printPathplan()
{
	if(status == SUCCESS) {
		
		envType aux[envMatrixX][envMatrixY];

		// creates temporary copy of the environment
		for (int i = 0; i < envMatrixY; i += 1)
			for (int j = 0; j < envMatrixX; j += 1)
				aux[j][i] = env[j][i];

		// fills the Points positions
		for(unsigned int i=0; i<path.size(); i++) {
			Point p = getPathNodeCell(i);
			aux[(int)p.getX()][(int)p.getY()] = PATH;
		}
		
		// put markers on initial and final positions
		aux[(int)initialpos.getX()][(int)initialpos.getY()] = MARKER1;
		aux[(int)finalpos.getX()][(int)finalpos.getY()] = MARKER2;
		
		// print a separator
		for (int x = 0; x < envMatrixX; x++)
			cout<<"_";
		cout<<endl;
		
		// print it all
		for (int i = 0; i < envMatrixY; i += 1) {
			for (int j = 0; j < envMatrixX; j += 1) {
				switch (aux[j][i]){
					case OBSTACLE: cout << "#"; break;
					case PATH: cout << "o"; break;
					case MARKER1: cout << "I"; break;
					case MARKER2: cout << "F"; break;
					default: cout << " "; break;
				}
			}
			cout << endl;
		}
	
	}

}

void Pathplan::fillEnv()
{
	int centerx, centery;

	for (int x = 0; x < envMatrixX; x++)
		for (int y = 0; y < envMatrixY; y++)
			env[x][y] = FREE;

	for(unsigned int i=0; i<obstacles.size(); i++) {
		centerx = round( MM_TO_CELLS_X(obstacles[i].getX()) );
		centery = round( MM_TO_CELLS_Y(obstacles[i].getY()) );
		fillEnv_playerBox(centerx,centery);
	}
}

Point Pathplan::getPathNodeMM(int pointIndex)
{
	Point p = getPathNodeCell(pointIndex);
	
	if( p.getX()==-1 && p.getY()==-1 )
		return p;
	else
		return Point( CELLS_TO_MM_X(p.getX()),
					  CELLS_TO_MM_Y(p.getY()) );
}

Point Pathplan::getPathNodeCell(int pointIndex)
{
	if( pointIndex>=0 && (unsigned int)pointIndex<path.size() )
		return path[pointIndex];
	else
		return Point(-1,-1);
}

Point Pathplan::getInitialPos()
{
	return Point( CELLS_TO_MM_X(initialpos.getX()), CELLS_TO_MM_Y(initialpos.getY()) );	
}
		
Point Pathplan::getFinalPos()
{
	return Point( CELLS_TO_MM_X(finalpos.getX()), CELLS_TO_MM_Y(finalpos.getY()) );
}

void Pathplan::setInitialPos(Point pos)
{
	initialpos = Point( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

void Pathplan::setFinalPos(Point pos)
{
	finalpos = Point( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}
