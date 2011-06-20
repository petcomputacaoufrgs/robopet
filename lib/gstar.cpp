#include "gstar.h"
#include "point.h"
#include "math.h"
#define PARTES 50//nr de partes que dividimos a reta
#define LADO_QUADRADO (4*ROBOT_RADIUS_MM + 2*TRESHOLD)//lado do quadrado de segurança
#define DIST_ROBO_POINT ((LADO_QUADRADO*sqrt(2))/2)
#define M (finalpos.getY() - initialpos.getY())/(finalpos.getX() - initialpos.getX())
using namespace std;

GStar::GStar() {}

GStar::~GStar() {}

void GStar::run() {
	Point actual;
	Obstacle o;

	obst.clear();

	setRadius(ROBOT_RADIUS_MM);
	setTreshold(ROBOT_RADIUS_MM/2);
	setSecureDistance();

	if(straightIsBlocked(initialpos, finalpos))
	{
		makePoints( M, obst.back().center);
	}

	//chama essa e está pronto o caminho ;D
	//goToEnd(initialpos, finalpos);
}

void GStar::goToEnd(Point actual, Point final)
{
	if(straightIsBlocked( actual, final))
	{//vai tentando ir pro A e B
		makePoints ( M, obst.back().center);		
		goToEndA(actual, obst.back().p[0]); //Actual->A
		goToEndB(actual, obst.back().p[1]); //Actual->B
	}
	else
	{//conseguiu ir pro ponto final		
			//bota na arvore actual->final
		//testa se o ponto final é realmente o finalzão lá
		if((final.getX() == finalpos.getX()) && (final.getY() == finalpos.getY()))
		{
				//é o fim :'(
		}
		else
			goToEnd(final, finalpos);		
	}	
}

void GStar::goToEndA(Point actual, Point final)
{
	if(straightIsBlocked( actual, final))
	{//vai tentando ir pro A
		makePoints ( M, obst.back().center);		
		goToEnd(actual, obst.back().p[0]); //Actual->A		
	}
	else
	{//conseguiu ir pro A tenta ir pra C
		//adiciona actual->final na árvore e tenta ir pro C
		goToEnd(final, obst.back().p[2]); //A->C		
	}
}

void GStar::goToEndB(Point actual, Point final)
{
	if(straightIsBlocked( actual, final))
	{//vai tentando ir pro B
		makePoints ( M, obst.back().center);		
		goToEnd(actual, obst.back().p[1]); //Actual->B
	}
	else
	{//conseguiu ir pro B, tenta ir pra D
		//adiciona actual->final na árvore e tenta ir pro D
		goToEnd(final, obst.back().p[3]); //B->D
	}
}

/* Seta um distância na qual os robos que passarem por ela, estarão levemente distantes do robô obstáculo*/
void GStar::setSecureDistance()
{
	this->secureDistance = ((((4*radius)+(2*treshold))*sqrt(2))/2.);
}

bool GStar::straightIsBlocked(Point initial, Point final) //Return true if straightIsBlocked
{
	double x,y;
	double centerx,centery;
	double comprimentoR, dist, m, xp, varX;
	double initialX = initial.getX();
	double initialY = initial.getY();
	double finalX = final.getX();
	double finalY = final.getY();
	Obstacle vert;

	comprimentoR = initial.getDistance(finalpos);	//comprimento da reta

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
			if(Point(centerx,centery).getDistance(Point(x,y)) <= (radius + treshold))
			{
				vert.center = Point(centerx, centery);
				obst.push_back(vert);
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

void GStar::makePoints(double m, Point p)
{
	double centerX = p.getX();
	double centerY = p.getY();
	double angle,mAD, mBC;
	double varX, varY;
	Point temp;
	Obstacle vert = obst.back();
	obst.pop_back();

	
	varX = finalpos.getX()-initialpos.getX();
	varY = finalpos.getY()-initialpos.getY();

	angle = atan(m) - 0.785398163; //-45°
	
	mAD = tan(angle);
	mBC = -1/mAD;

	if((abs(varX)==varX && abs(varY)==varY) || (abs(varX)!=varX && abs(varY)!=varY))
	{
		vert.p[0].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
		vert.p[0].setY((mAD*(vert.p[0].getX()-centerX))+centerY);
		vert.p[3].setX(centerX - vert.p[0].getX() + centerX);
		vert.p[3].setY((mAD*(vert.p[3].getX()-centerX))+centerY);
		
		if(mBC>0)
		{
			vert.p[2].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
			vert.p[2].setY((mBC*(vert.p[2].getX()-centerX))+centerY);
			vert.p[1].setX(centerX - vert.p[2].getX() + centerX);
			vert.p[1].setY((mBC*(vert.p[1].getX()-centerX))+centerY);
		}
		else
		{
			vert.p[1].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
			vert.p[1].setY((mBC*(vert.p[1].getX()-centerX))+centerY);
			vert.p[2].setX(centerX - vert.p[1].getX() + centerX);
			vert.p[2].setY((mBC*(vert.p[2].getX()-centerX))+centerY);
		}
	}
	else
	{
		vert.p[1].setX((DIST_ROBO_POINT/sqrt((mBC*mBC)+1))+centerX);
		vert.p[1].setY((mBC*(vert.p[1].getX()-centerX))+centerY);
		vert.p[2].setX(centerX - vert.p[1].getX() + centerX);
		vert.p[2].setY((mBC*(vert.p[2].getX()-centerX))+centerY);
		
		if(mAD>0)
		{
			vert.p[3].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
			vert.p[3].setY((mAD*(vert.p[3].getX()-centerX))+centerY);
			vert.p[0].setX(centerX - vert.p[3].getX() + centerX);
			vert.p[0].setY((mAD*(vert.p[0].getX()-centerX))+centerY);
		}
		else
		{
			vert.p[0].setX((DIST_ROBO_POINT/sqrt((mAD*mAD)+1))+centerX);
			vert.p[0].setY((mAD*(vert.p[0].getX()-centerX))+centerY);
			vert.p[3].setX(centerX - vert.p[0].getX() + centerX);
			vert.p[3].setY((mAD*(vert.p[3].getX()-centerX))+centerY);
		}
	}
	if(abs(varX)!=varX)
	{
		temp = vert.p[0];
		vert.p[0] = vert.p[3];
		vert.p[3] = temp;
	}
	if(abs(varY)==varY)
	{
		temp = vert.p[1];
		vert.p[1] = vert.p[2];
		vert.p[2] = temp;
	}
	obst.push_back(vert);
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

Obstacle GStar::getLastObstacle()
{
	return obst.back();
}

Obstacle GStar::getObstacle(int n)
{
	return obst[n];
}

int GStar::getObstaclesSize()
{
	return obst.size();
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
