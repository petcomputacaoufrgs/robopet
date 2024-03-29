#include <iostream>
#include <stdlib.h>

#include "utils.h"

#include "discretePathplan.h"

DiscretePathplan::DiscretePathplan()
{
	this->radius = OBSTACULE_RADIUS;
	
	envMatrixX = ENV_MATRIX_SIZE_X;
	envMatrixY = (int)(envMatrixX * (FIELD_HEIGHT_MM/(float)FIELD_WIDTH_MM) + 1);
	
	env = (envType**) allocMatrix(envMatrixX,envMatrixY,sizeof(envType),sizeof(envType*));
	
	for (int i = 0; i < envMatrixX; i += 1)
		for (int j = 0; j < envMatrixY; j += 1)
            env[i][j] = FREE;
}

DiscretePathplan::~DiscretePathplan() {}


void DiscretePathplan::fillEnv()
{
	int centerx, centery;

	for (int x = 0; x < envMatrixX; x++)
		for (int y = 0; y < envMatrixY; y++)
			env[x][y] = FREE;

	for(unsigned int i=0; i<obstacles.size(); i++) {
		centerx = round( MM_TO_CELLS_X(obstacles[i].pos.getX()) );
		centery = round( MM_TO_CELLS_Y(obstacles[i].pos.getY()) );
		fillEnv_playerBox(centerx,centery);
	}
}

int DiscretePathplan::getRadius()
{
	return radius;
}

void DiscretePathplan::setRadius(int radius)
{
	this->radius = radius;
}

void DiscretePathplan::setEnvXY( int x, int y )
{
	envMatrixX = x;
	envMatrixY = y;

	if(env) free(env);
	env = (envType**) allocMatrix(envMatrixX,envMatrixY,sizeof(envType),sizeof(envType*));
}

int DiscretePathplan::getEnvMatrixX()
{
	return envMatrixX;
}

int DiscretePathplan::getEnvMatrixY()
{
	return envMatrixY;
}

void DiscretePathplan::printEnv()
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

void DiscretePathplan::printPathplan()
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

void DiscretePathplan::fillEnv_playerBox(int x, int y)
{
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

bool DiscretePathplan::isLineBlocked(Point p1, Point p2)
/* The idea is to use the algorithm of Bresenham for rasterizing a 
line in a grid, and then using the raster points to test for obstacles.*/
{
	int x1 = p1.getX(); 
	int x2 = p2.getX(); 
	int y1 = p1.getY(); 
	int y2 = p2.getY(); 

	int slope; 
	int dx, dy, incE, incNE, d, x, y; 
	// Onde inverte a linha x1 > x2 
	if (x1 > x2){ 
			return isLineBlocked(p2, p1); 
	} 
	
	// line is parallel with Y Axis
	if(x1 == x2){
		if(y1 < y2) { 
			for(y = y1; y <= y2; y++) 
				if (env[x1][y] == OBSTACLE)
					return true;
		} 
		else 
			for(y = y2; y <= y1; y++) 
				if (env[x1][y] == OBSTACLE)
					return true; 
	} 
	else{ 
		   dx = x2 - x1; 
		   dy = y2 - y1; 

		   if (dy < 0){ 
			   slope = -1; 
			   dy = -dy; 
		   } 
		   else{ 
			  slope = 1; 
		   } 
		   // constant of Bresenham 
		   incE = 2 * dy; 
		   incNE = 2 * dy - 2 * dx; 
		   d = 2 * dy - dx; 
		   y = y1; 
		   for (x = x1; x <= x2; x++){ 
			   if (env[x][y] == OBSTACLE)
				  return true; 

			   if (d <= 0){ 
				 d += incE; 
			   } 
			   else{ 
				 d += incNE; 
				 y += slope; 
			   } 
		   } 

		   return false; 
	} 

	return false;
 } 

Point DiscretePathplan::getPathNode(int pointIndex)
{
	if( pointIndex>=0 && (unsigned int)pointIndex<path.size() )
		return path[pointIndex];
	else
		return Point(-1,-1);
}

Point DiscretePathplan::getPathNodeCell(int pointIndex)
{
	Point p = getPathNode(pointIndex);
	
	if( p.getX()==-1 && p.getY()==-1 )
		return p;
	else
		return Point( MM_TO_CELLS_X(p.getX()),
					  MM_TO_CELLS_Y(p.getY()) );
}

Point DiscretePathplan::getInitialPos()
{
	return Point( CELLS_TO_MM_X(initialpos.getX()), CELLS_TO_MM_Y(initialpos.getY()) );	
}
		
Point DiscretePathplan::getFinalPos()
{
	return Point( CELLS_TO_MM_X(finalpos.getX()), CELLS_TO_MM_Y(finalpos.getY()) );
}

void DiscretePathplan::setInitialPos(Point pos)
{
	initialpos = Point( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}

void DiscretePathplan::setFinalPos(Point pos)
{
	finalpos = Point( round(MM_TO_CELLS_X( pos.getX() )), round(MM_TO_CELLS_Y( pos.getY() )) );
}
