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

	setRadius(ROBOT_RADIUS_MM);
	setTreshold(ROBOT_RADIUS_MM/2);
	setSecureDistance();

//	cout<<straightIsBlocked(initialpos, finalpos)<<endl;

	//chama essa e está pronto o caminho ;D
	goToEnd();
}

void GStar::calcCost(PathCost *p)
{
	p->cost = (p->origin).getDistance(p->dest);
}

void GStar::goToEnd()
{
	cout << "***********************COMEÇO************************" << endl;
	StackPoint temp;
	StackPoint ret;
	Point actual;
int k = 1;

	bool chegou = false;

	path.push_back(initialpos);

	actual = initialpos;

		for(int i = 0; i < 5; i++)
	//	while(!points.empty() && !chegou)
		{
			cout<<"entrou no while"<<endl;
			if(straightIsBlocked(actual, finalpos, &ret))
			{cout<<"actual->fim bloqueado"<<endl;
				ret.p=1;
				points.push(ret);
				ret.p=0;
				points.push(ret);
			
				temp = points.top();
				points.pop();

		//		cout<<"A- X: "<<obst[temp.obstacle_id].p[temp.p].getX()<<" Y: "<<obst[temp.obstacle_id].p[temp.p].getY()<<endl;
				if(straightIsBlocked(actual, obst[temp.obstacle_id].p[temp.p], &ret)) //se do inicio->A ou B
				{
					cout<<"actual->A bloqueado"<<endl;

					ret.p=1;
					points.push(ret);
					ret.p=0;
					points.push(ret);
				}
				else//conseguiu inicio->A/B
				{
					cout<<"foi actual->A"<<endl;

					path.push_back(obst[temp.obstacle_id].p[temp.p]); //A ou B no caminho
			//		cout<<"C: ("<<obst[temp.obstacle_id].p[temp.p+2].getX()<<","<<obst[temp.obstacle_id].p[temp.p+2].getY()<<")"<<endl;
					if(straightIsBlocked(obst[temp.obstacle_id].p[temp.p], obst[temp.obstacle_id].p[temp.p+2], &ret)) 
					{
						cout<<"A->C bloqueado"<<endl;							//tenta A->C / B->D
						ret.p=1;
						points.push(ret);
						ret.p=0;
						points.push(ret);
				
						actual = obst[temp.obstacle_id].p[temp.p];
					}
					else//conseguiu
					{
						cout<<"foi A->C"<<endl;
						path.push_back(obst[temp.obstacle_id].p[temp.p+2]); //C ou D no caminho

						temp.p +=2;
						actualPoints.push(temp);
						temp = actualPoints.top();
						actualPoints.pop();
						actual = obst[temp.obstacle_id].p[temp.p];
					}
				}
			}
			else
			{cout<<"foi Actual-> fim"<<endl;
				path.push_back(finalpos);
				if(actualPoints.empty() && k == 1)
				{
					actual = initialpos;
					k = 0;
				}
			}
	}

	cout << "***********************FIM***********************" << endl;
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
	//cout << "0 = "<<Azinho<<"x + "<<Bzinho<<"y + "<<Czinho<<endl;
	
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


//void ordena_obstáculos(point origem, vector obstáculos)
	/*ordena o vetor de obstáculos de acordo com a proximidade da origem
	para saber qual foi o primeiro ponto que bloqueou o caminho*/
	
//point descobre_obstáculo(point origem, point final, vector obstáculos)
	/*retorna qual é o primeiro ponto que está no caminho origem-final
	do robô*/
	

	
/*
a partir desse ponto, já é possível verificar se é possível ir da 
origem até os pontos A e B. Basta chamas a "vai_até_o_fim?" com "final"
sendo A ou B, e isso retorna o booleano correto.
*/

/*
após isso, devemos chama a mesma "vai_até_o_fim?" mas somente de A-C ou 
B-D, pois outras permutações cruzam o robô.
*/

//void joga_no_grafo_reta(point origem, point final)
	/*manda uma reta entre os dois pontos no grafo, atribuindo seu custo*/
	
//void joga_no_grafo_ponto(point ponto)
	/*poe no grafo os pontos indicados na passagem da função. Pode ser 
	inserida na "cria_pontos".*/
	
/*fazer aqui a manolisse de testar se é possível ir da origem pro final, 
só pelo lolz, e se der poe no grafo, senão esquece.
*/

/*a ideia é ir na recursão tentando chegar no F, indo sempre pelos 2 
lados do robô obstáculo tentando ir até o final, e parando caso esteja 
tentando ir para um ponto que já havia sido calculado.
*/


// ...
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
Point GStar::getPathNode(int pointIndex) {
	// do me ;)
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
