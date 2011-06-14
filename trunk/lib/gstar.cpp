#include "gstar.h"
#include "point.h"
#define PARTES 50//nr de partes que dividimos a reta

using namespace std;

GStar::GStar() {

}

GStar::~GStar() {}


void GStar::run() {
	setRadius(300);
	setTreshold(150);
	setSecureDistance();
	cout << straightIsBlocked() << endl;
}

void GStar::setSecureDistance()
{
	this->secureDistance = ((((4*radius)+(2*treshold))*sqrt(2))/2.);
}

bool GStar::straightIsBlocked() //Return true if straightIsBlocked
{
	double x,y;
	double centerx,centery;
	double comprimentoR, dist, m, xp, varX;
	double initialX = initialpos.getX();
	double initialY = initialpos.getY();
	double finalX = finalpos.getX();
	double finalY = finalpos.getY();

	comprimentoR = initialpos.getDistance(finalpos);	//comprimento da reta

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
				return true; //obstaculo
		}
		if(initialX < finalX)
			x = x+varX;
		else
			x = x-varX;
	}
	return false;
}

bool GStar::straightIsBlockedB()
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
	Azinho = (initialY - finalY);
	Bzinho = (finalX - initialX);
	Czinho = ((initialX * finalY) - (finalX * initialY));
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
		else
			return false;
	}
}

//void createPoints()
	/*cria os 4 pontos ABCD ao redor do obstáculo e armazena numa 
	estrutura*/
void GStar::makePoints()
{
	double centerx,centery;

	for(unsigned int j=0; j<obstacles.size(); j++) { 
		centerx = (obstacles[j].pos.getX());
		centery = (obstacles[j].pos.getY());		
	}

	
}

/* São necessários mesmo esses getters e setters?
 * Só faz sentido fazer esse tipo de coisa quando há um tratamento a mais envolvido. Por exemplo, uma conversão de coordenadas.
 * Nesse caso aqui acho que é uma complicação desnecessária ;)
 */


	
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
