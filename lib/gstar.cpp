#include "gstar.h"
#include "point.h"
#include "math.h"
#include <cstdlib>
#define PARTES 60//nr de partes que dividimos a reta
#define LADO_QUADRADO (6*ROBOT_RADIUS_MM)//lado do quadrado de segurança
#define DIST_ROBO_POINT ((LADO_QUADRADO*sqrt(2))/2)
#define M (finalpos.getY() - initialpos.getY())/(finalpos.getX() - initialpos.getX())
using namespace std;

GStar::GStar() {}

GStar::~GStar() {}

void GStar::run() {
	Point actual;
	Obstacle o;
	double distance;
	double minDistance=INFINITY;
	
	clockBase = clock();

	obst = (Obstacle*) calloc(obstacles.size(), sizeof(Obstacle));
	for(unsigned int i=0; i<obstacles.size(); i++)
	{
		for(int j=0; j<4; j++)
		{
			obst[i].p[j].setX(-1);
			obst[i].p[j].setY(-1);
		}
	}

	path.clear();
	paths.clear();

	setRadius(ROBOT_RADIUS_MM);
	setTreshold(ROBOT_RADIUS_MM/2);
	setSecureDistance();

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
		//cout<<paths.size()<<endl;
	}
	else
	{
		if(status != ERROR_TIMELIMIT)
			status = ERROR_UNREACHABLE;
	}
	

	for (unsigned int i=0; i<paths.size(); i++)
	{
		distance=0;
		for(unsigned int j=0; j<paths[i].size()-1; j++)
		{
			distance += paths[i][j].getDistance(paths[i][j+1]);
		}
		if(distance < minDistance)
		{
			minDistance = distance;
			path = paths[i];
		}
	}
	//cout<<minDistance<<endl;
}

void GStar::bestWay()
{
	StackPoint ret;
	vector<Point> tmp_path;
	int trocou=0,j,k;
	for(int i=paths.size()-1; i>=0; i--)
	{
		tmp_path = paths[i];
		
		j = tmp_path.size()-1;
		while(j>0 && trocou == 0)
		{
			k=0;
			while(straightIsBlocked(tmp_path[k], tmp_path[j], &ret) && k < j-1)
				k++;
						
			if(k < j-1) //se achou um atalho
			{
				//cout << "achou atalho" << endl;
				tmp_path.erase(tmp_path.begin()+k+1,tmp_path.begin()+j);
				trocou = 1;
			}
			j--;		
		}
		if(trocou)
		{
		//	cout << "trocou o/" << endl;
			paths.push_back(tmp_path);
		}	
		trocou = 0;	
	}	
}

bool GStar::pointIsInsideRobot(Point p)
{
	for(unsigned int j=0; j<obstacles.size(); j++) 
	{					
			//equação circunferencia, se da dentro do circulo			 
			if(obstacles[j].pos.getDistance(p) <= (4*radius + treshold))
				
				return true; //obstaculo
	}
	
	return false;
} 

vector<Point> GStar::walkA(vector<Point> aPath, Point final, int obstID)
{
	StackPoint ret;
	Point actual = aPath.back();
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > 0.05 )) 
	{
		if(!pointIsInsideRobot(final))
		{
			if(straightIsBlocked(actual, obst[obstID].p[0], &ret))
			{//actual->A bloqueado, e agora?
				//cout<<"actual->A bloqueado"<<endl;
				if(ret.obstacle_id != obstID)
				{
					//cout << "Nao se bateu" << endl;
					return walkA(aPath, finalpos, ret.obstacle_id);
				}	
				else
				{
					//cout << "Se bateu fecha caminho" << endl;
					aPath.empty();
					return aPath;	
				}
			}
			else
			{//foi actual->A
				actual = obst[obstID].p[0];
				aPath.push_back(actual);
				
				if(straightIsBlocked(actual, obst[obstID].p[2], &ret))
				{//A->C bloqueado, e agora?
					aPath.pop_back();			
					//cout<<"A->C bloqueado"<<endl;
					return walkA(aPath, finalpos, ret.obstacle_id);
								
				}
				else
				{//foi A->C
					actual = obst[obstID].p[2];
					aPath.push_back(actual);			
					aPath = walk(aPath); //continua caminho
					return aPath;
				}
			}
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
			return aPath;
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
		return aPath;
	}
}

vector<Point> GStar::walkB(vector<Point> aPath, Point final, int obstID)
{
	StackPoint ret;
	Point actual = aPath.back();
	
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > 0.05 )) 
	{
		if(!pointIsInsideRobot(final))
		{
			if(straightIsBlocked(actual, obst[obstID].p[1], &ret))
			{
				//cout<<"actual->B bloqueado"<<endl;
				if(ret.obstacle_id != obstID)
					return walkB(aPath, finalpos, ret.obstacle_id);
				else
				{
					//cout << "Se bateu fecha caminho" << endl;
					aPath.empty();
					return aPath;	
				}
				
			}
			else
			{//foi actual->B
				actual = obst[obstID].p[1];
				aPath.push_back(actual);
				
				if(straightIsBlocked(actual, obst[obstID].p[3], &ret))
				{
					aPath.pop_back();			
					//cout<<"B->D bloqueado"<<endl;
					return walkB(aPath, finalpos, ret.obstacle_id);
				}
				else
				{//foi B->D
					actual = obst[obstID].p[3];
					aPath.push_back(actual);
					aPath = walk(aPath); //continua caminho
					return aPath;
				}
			}
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
			return aPath;
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
		return aPath;
	}
}

vector<Point> GStar::walk(vector<Point> aPath)
{
	StackPoint ret;
	vector<Point> pathA;
	vector<Point> pathB;
	Point actual = aPath.back();
	
	if(!(((clock() - clockBase)/(float)CLOCKS_PER_SEC ) > 0.05 )) 
	{
		if(!pointIsInsideRobot(finalpos))
		{	
			if(straightIsBlocked(actual, finalpos, &ret))
			{
				if(obst[ret.obstacle_id].p[2] != actual && obst[ret.obstacle_id].p[3] != actual)
				{//aqui ele nao esta se batendo
					pathA = walkA(aPath, finalpos, ret.obstacle_id);
					pathB = walkB(aPath, finalpos, ret.obstacle_id);
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
					return aPath;	
				}			
			}
			else
			{			
				aPath.push_back(finalpos);
				//paths.push_back(aPath);
			}
			return aPath;
		}
		else
		{
			//cout << "Ponto dentro do robo" << endl;
			aPath.empty();
			return aPath;
		}
	}
	else
	{
		status = ERROR_TIMELIMIT;
		aPath.empty();
		return aPath;
	}
}

/* Seta um distância na qual os robos que passarem por ela, estarão levemente distantes do robô obstáculo*/
void GStar::setSecureDistance()
{
	this->secureDistance = ((((4*radius)+(2*treshold))*sqrt(2))/2.);
}

bool GStar::straightIsBlocked(Point initial, Point final, StackPoint* temp) //Return true if straightIsBlocked
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
			if(Point(centerx,centery).getDistance(Point(x,y)) <= (2*radius + treshold))
			{
				temp->obstacle_id = j;
				makePoints(j);
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

bool GStar::straightIsBlockedB() //provavelmente ta testando obstaculos que estao fora da trajetoria...
{
	double centerx,centery;
	double dist;
	double initialX = initialpos.getX();
	double initialY = initialpos.getY();
	double finalX = finalpos.getX();
	double finalY = finalpos.getY();
	double A, B, C;

	//dá pra calcular a distancia do ponto a reta com 1 fórmula só, e nao precisa iterar pra caralho.
	//a questão é delimitar origem e fim da reta, pra nao calcular quem tá depois.
	//segue aqui o método de sarrus, simplificado, pra achar a equação geral da reta:
	A = (initialY - finalY);
	B = (finalX - initialX);
	C = ((initialX * finalY) - (finalX * initialY));
	////cout << "0 = "<<Azinho<<"x + "<<Bzinho<<"y + "<<Czinho<<endl;
	
	//x e y aqui são os mesmos do robô, os quais devem ser iterados uma só vez
	//dist = (abs(x*Azinho + y*Bzinho + Czinho) / sqrt((Azinho*Azinho) + (Bzinho*Bzinho)))

	for(unsigned int j=0; j<obstacles.size(); j++) { //para cada obstaculo ve se ele bate na reta
		centerx = (obstacles[j].pos.getX());
		centery = (obstacles[j].pos.getY());
		dist = (abs(centerx*A + centery*B + C)/sqrt((A*A) + (B*B)));						
		//equação circunferencia, se da dentro do circulo			 
		if(dist <= (radius + treshold))
			return true; //obstaculo
	}
	return false;
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

		angle = atan(M) - 0.785398163; //-45°
	
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

void GStar::setRadius(int radius) {
	this->radius = radius;
}

void GStar::setTreshold(int treshold ){
	this->treshold = treshold;
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
