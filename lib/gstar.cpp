#include "gstar.h"
#include "point.h"
#include "math.h"
//#include <cstdlib>
using namespace std;


#define PARTES 60//nr de partes que dividimos a reta
#define LADO_QUADRADO (6*ROBOT_RADIUS_MM)//lado do quadrado de segurança
#define DIST_ROBO_POINT ((LADO_QUADRADO*sqrt(2))/2)
#define GSTAR_TIMELIMIT 0.05

#define _TRESHOLD (ROBOT_RADIUS_MM/2)
#define LIMIT_INSIDE_ROBOT (4*ROBOT_RADIUS_MM + _TRESHOLD)
#define LIMIT_IS_BLOCKED (2*ROBOT_RADIUS_MM + _TRESHOLD)


GStar::GStar() {}

GStar::~GStar() {}

void GStar::run() {
	Point actual;
		
	clockBase = clock();
	
	path.clear();
	paths.clear();
	
	obst = new Obstacle[obstacles.size()];
	
	for(unsigned int i=0; i<obstacles.size(); i++)
	{
		for(int j=0; j<4; j++)
		{
			obst[i].p[j].setX(-1);
			obst[i].p[j].setY(-1);
		}
	}

	vector<Point> aPath;
	aPath.push_back(initialpos);
	aPath = walk(aPath);
	
	if(aPath.back() == finalpos)
		paths.push_back(aPath);
	
	if(paths.size()>0)
	{
		status = SUCCESS;
		bestWay();
    	elapsedTime = (clock() - clockBase)/(float)CLOCKS_PER_SEC;
	}
	else
	{
		if(status != ERROR_TIMELIMIT)
			status = ERROR_UNREACHABLE;
	}
}

void GStar::bestWay()
{
	int obstId, j, shortcut;
	vector<Point> tmp_path;
	double distance, minDistance=INFINITY;
	
	for(unsigned int i=0; i<paths.size(); i++)
	{
		tmp_path = paths[i];
		distance = 0;
		shortcut = 0;
		j = 0;
		
		while (j < tmp_path.size()-1) // find shortcuts in the path
		{
			for (unsigned int k=tmp_path.size()-1; k > j+1 && (shortcut ==0) ; k--) {
				if (!straightIsBlocked(tmp_path[j], tmp_path[k], &obstId)) {
					//cout << "opa achou atalho!" << endl;
					shortcut=k;
				}
			}
			
			if (shortcut != 0) {
				tmp_path.erase(tmp_path.begin()+j+1, tmp_path.begin()+shortcut); // clean the path if find a shortcut
				distance += tmp_path[j].getDistance(tmp_path[shortcut]);
				shortcut=0;
			}
			else {
				distance += tmp_path[j].getDistance(tmp_path[j+1]);
			}
				
			j++;
		}
		
		paths[i] = tmp_path; // update the path
		
		if (distance < minDistance) { //saves the best the path
			minDistance = distance;
			path = paths[i];
		}
	}
	
	//cout << minDistance << endl;
}


bool GStar::pointIsInsideRobot(Point p)
{	
	for(unsigned int j=0; j<obstacles.size(); j++) 
	{					
			//equação circunferencia, se da dentro do circulo			 
			if(obstacles[j].pos.getDistance(p) <= LIMIT_INSIDE_ROBOT)
								return true; //obstaculo
	}
	
	return false;
} 

vector<Point> GStar::walkA(vector<Point> aPath, Point final, int obstID)
{
	int ret;
	Point actual = aPath.back();
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > GSTAR_TIMELIMIT )) 
	{
		if(!pointIsInsideRobot(final))
		{
			if(straightIsBlocked(actual, obst[obstID].p[0], &ret))
			{//actual->A bloqueado, e agora?
				makePoints(ret);
				
				//cout<<"actual->A bloqueado"<<endl;
				if(ret != obstID) {
					//cout << "Nao se bateu" << endl;
					return walkA(aPath, finalpos, ret);
				}	
				else
				{
					//cout << "Se bateu fecha caminho" << endl;
					aPath.empty();
				}
			}
			else
			{//foi actual->A
				actual = obst[obstID].p[0];
				
				if(straightIsBlocked(actual, obst[obstID].p[2], &ret))
				{//A->C bloqueado, e agora?
					makePoints(ret);
						
					//cout<<"A->C bloqueado"<<endl;
					return walkA(aPath, finalpos, ret);			
				}
				else
				{//foi A->C
					aPath.push_back(actual);
					aPath.push_back(obst[obstID].p[2]);			
					aPath = walk(aPath); //continua caminho
				}
			}
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
	}
	
	return aPath;
}

vector<Point> GStar::walkB(vector<Point> aPath, Point final, int obstID)
{
	int ret;
	Point actual = aPath.back();
	
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > GSTAR_TIMELIMIT )) 
	{
		if(!pointIsInsideRobot(final))
		{
			if(straightIsBlocked(actual, obst[obstID].p[1], &ret))
			{
				makePoints(ret);
				
				//cout<<"actual->B bloqueado"<<endl;
				if(ret != obstID) {
					return walkB(aPath, finalpos, ret);
				}
				else
				{
					//cout << "Se bateu fecha caminho" << endl;
					aPath.empty();	
				}
			}
			else
			{//foi actual->B
				actual = obst[obstID].p[1];
				
				if(straightIsBlocked(actual, obst[obstID].p[3], &ret))
				{
					makePoints(ret);
			
					//cout<<"B->D bloqueado"<<endl;
					return walkB(aPath, finalpos, ret);
				}
				else
				{//foi B->D
					aPath.push_back(actual);
					aPath.push_back(obst[obstID].p[3]);
					aPath = walk(aPath); //continua caminho
				}
			}
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
	}
	
	return aPath;
}

vector<Point> GStar::walk(vector<Point> aPath)
{
	int ret;
	vector<Point> pathA;
	vector<Point> pathB;
	Point actual = aPath.back();
	
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > GSTAR_TIMELIMIT )) 
	{
		if(!pointIsInsideRobot(finalpos))
		{	
			if(straightIsBlocked(actual, finalpos, &ret))
			{
				makePoints(ret);
				
				if(obst[ret].p[2] != actual && obst[ret].p[3] != actual)
				{//aqui ele nao esta se batendo
					pathA = walkA(aPath, finalpos, ret);
					pathB = walkB(aPath, finalpos, ret);
					
					if(pathA.back() == finalpos)
					{
						//cout << "chegou no fim A" << endl;
						paths.push_back(pathA);
					}
					
					if(pathB.back() == finalpos)
					{
						//cout << "chegou no fim B" << endl;
						paths.push_back(pathB);
					}
				}	
				else
				{//aqui ele ta se batendo
					//cout << "Se bateu fecha caminho" << endl;
					aPath.empty();	
				}			
			}
			else
			{			
				aPath.push_back(finalpos);
			}
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
	}
	
	return aPath;
}

bool GStar::validatePath(Point newGoal, int maxvar)
{
	int foo;
	
	if(getFinalPos().getDistance(newGoal) > maxvar)
		return false;
	else {
		for(unsigned int i=0; i<path.size()-1; i++)
			if(straightIsBlocked( getPathNode(i), getPathNode(i+1), &foo))
				return false;
	}
		
	return true;
}

bool GStar::straightIsBlockedDiscrete(Point initial, Point final, int* obstId)
{
	double x,y;
	double centerx,centery;
	double comprimentoR, dist, m, xp, varX;
	double initialX = initial.getX();
	double initialY = initial.getY();
	double finalX = final.getX();
	double finalY = final.getY();

	comprimentoR = initial.getDistance(final);	//comprimento da reta

	dist = comprimentoR/PARTES;
	
	m = (finalY - initialY)/(finalX - initialX);
	xp=(dist/sqrt(1+m*m))+initialX;
	varX = xp - initialX;
		
	x = initialX; // x começa no inicio
	for(int i = 0; i<PARTES; i++)
	{
		y = (m*(x-initialX))+initialY;
				
		for(unsigned int j=0; j<obstacles.size(); j++) { //para cada obstaculo ve se ele bate na reta
			
			centerx = (obstacles[j].pos.getX());
			centery = (obstacles[j].pos.getY());							
			//equação circunferencia, se da dentro do circulo			 
			if(Point(centerx,centery).getDistance(Point(x,y)) <= LIMIT_IS_BLOCKED)
			{
				*obstId = j;
				return true; //obstaculo
			}
		}
		if(initialX < finalX)
			x = x+varX;
		else
			x = x-varX;
	}
	return false;
}

bool GStar::straightIsBlocked(Point p1, Point p2, int* obstId)
{
	double obsx,obsy;
	double dist, distToInitp1, smallestDist=INFINITY;
	double distPts = p1.getDistance(p2) + _TRESHOLD;
	double initialX = p1.getX();
	double initialY = p1.getY();
	double finalX = p2.getX();
	double finalY = p2.getY();
	double a, b, c;
	double sqrtAB;	
	bool isBlocked=false;

	//Sarrus Method to obtain parameters of line's equation
	a = (initialY - finalY);
	b = (finalX - initialX);
	c = ((initialX * finalY) - (finalX * initialY));
	
	sqrtAB = sqrt((a*a) + (b*b));
	
	//x e y aqui são os mesmos do robô, os quais devem ser iterados uma só vez
	//dist = (abs(x*Azinho + y*Bzinho + Czinho) / sqrt((Azinho*Azinho) + (Bzinho*Bzinho)))
	for(unsigned int j=0; j<obstacles.size(); j++) { //para cada obstaculo ve se ele bate na reta
		obsx = (obstacles[j].pos.getX());
		obsy = (obstacles[j].pos.getY());
		dist = (abs(obsx*a + obsy*b + c)/sqrtAB);
		
		distToInitp1 = p1.getDistance(obstacles[j].pos);
		
		//test if obstacle is valid (isn't out of the line segment)
		if(distToInitp1 < distPts && obstacles[j].pos.getDistance(p2) < distPts)		
			if(dist <= LIMIT_IS_BLOCKED) { //test if obstructs
				isBlocked = true;
				
				if(distToInitp1 < smallestDist) {
				//use the distance to the inital point to determine the obstructing obstacle
					smallestDist = distToInitp1;
					*obstId = j;
				}
			}
	}
	
	return isBlocked;
}

void GStar::makePoints(int x)
{
	double centerX = obstacles[x].pos.getX();
	double centerY = obstacles[x].pos.getY();
	double angle,mAD, mBC;
	double varX, varY;
	Point temp;
	
	if(obst[x].p[0].getX()==-1) //se o X do ponto A for diferente de -1, já calculou os pontos!
	{
		varX = finalpos.getX()-initialpos.getX();
		varY = finalpos.getY()-initialpos.getY();

		angle = atan(varY / varX ) - 0.785398163; //-45°
	
		mAD = tan(angle);
		mBC = -1/mAD;

		if((abs(varX)==varX && abs(varY)==varY) || (abs(varX)!=varX && abs(varY)!=varY))
		{
			obst[x].p[3].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
			obst[x].p[3].setY((mAD*(obst[x].p[3].getX()-centerX))+centerY);
			obst[x].p[0].setX(centerX - obst[x].p[3].getX() + centerX);
			obst[x].p[0].setY((mAD*(obst[x].p[0].getX()-centerX))+centerY);
		
			if(mBC>0)
			{
				obst[x].p[1].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
				obst[x].p[1].setY((mBC*(obst[x].p[1].getX()-centerX))+centerY);
				obst[x].p[2].setX(centerX - obst[x].p[1].getX() + centerX);
				obst[x].p[2].setY((mBC*(obst[x].p[2].getX()-centerX))+centerY);
			}
			else
			{
				obst[x].p[2].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
				obst[x].p[2].setY((mBC*(obst[x].p[2].getX()-centerX))+centerY);
				obst[x].p[1].setX(centerX - obst[x].p[2].getX() + centerX);
				obst[x].p[1].setY((mBC*(obst[x].p[1].getX()-centerX))+centerY);
			}
		}
		else
		{
			obst[x].p[2].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
			obst[x].p[2].setY((mBC*(obst[x].p[2].getX()-centerX))+centerY);
			obst[x].p[1].setX(centerX - obst[x].p[2].getX() + centerX);
			obst[x].p[1].setY((mBC*(obst[x].p[1].getX()-centerX))+centerY);
		
			if(mAD>0)
			{
				obst[x].p[0].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
				obst[x].p[0].setY((mAD*(obst[x].p[0].getX()-centerX))+centerY);
				obst[x].p[3].setX(centerX - obst[x].p[0].getX() + centerX);
				obst[x].p[3].setY((mAD*(obst[x].p[3].getX()-centerX))+centerY);
			}
			else
			{
				obst[x].p[3].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
				obst[x].p[3].setY((mAD*(obst[x].p[3].getX()-centerX))+centerY);
				obst[x].p[0].setX(centerX - obst[x].p[3].getX() + centerX);
				obst[x].p[0].setY((mAD*(obst[x].p[0].getX()-centerX))+centerY);
			}
		}
		
		if(abs(varX)!=varX)
		{
			temp = obst[x].p[0];
			obst[x].p[0] = obst[x].p[3];
			obst[x].p[3] = temp;
		}
		
		if(abs(varY)==varY)
		{
			temp = obst[x].p[1];
			obst[x].p[1] = obst[x].p[2];
			obst[x].p[2] = temp;
		}
	}
}

Obstacle GStar::getObstacle(int n)
{
	return obst[n];
}

vector<Point> GStar::getPointPath()
{
	return path;
}
Point GStar::getPathNode(int pointIndex)
{
	return path[pointIndex];
}
				
void GStar::setInitialPos(Point pos) {
	initialpos = pos;
}		

void GStar::setFinalPos(Point pos) {
	finalpos = pos;
}

Point GStar::getInitialPos() {
	return initialpos;
}
		
Point GStar::getFinalPos() {
	return finalpos;
}
