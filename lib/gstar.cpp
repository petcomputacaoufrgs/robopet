#include "gstar.h"
#include "point.h"
#define PARTES 50

using namespace std;

GStar::GStar() {

}

GStar::~GStar() {}


void GStar::run() {
	
	cout << straightIsBlocked(initialpos,finalpos) << endl;
	
}


//bool vai_até_o_fim?(point origem, point final, vector obstáculos)
	/*totalmente algébrica. Deve verificar se uma reta está bloqueado em 
	qualquer ponto por um obstáculo. Retorna true se a reta estiver bloqueada*/
bool GStar::straightIsBlocked(Point initial, Point final)
{
	//equação da reta é ax+by+c=0
	double x,y;
	double centerx,centery;
	double comprimentoR, dist, m,delta,xp1,xp2,varX;

	comprimentoR = initial.getDistance(final);	//comprimento da reta

	dist = comprimentoR/PARTES; //nr de partes que dividimos a reta

	m = (final.getY() - initial.getY())/(final.getX() - initial.getX());
	delta = ((2*initial.getX())*(2*initial.getX())) - (4*-(((dist*dist)/(m*m)+1)-(2*initial.getX())*(2*initial.getX())));
	xp1 = (2*initial.getX() + sqrt(delta))/2;	
	xp2 = (2*initial.getX() - sqrt(delta))/2;

	if(initial.getX() < final.getX())
	{//soma
		if(xp1 > initial.getX())
			varX = xp1 - initial.getX();
		else
			varX = xp2 - initial.getX();		
	}
	else
	{//subtrai
		if(xp1 > initial.getX())
			varX = xp2 - initial.getX();
		else
			varX = xp1 - initial.getX();
	}

	
	//vamos percorrer toda a reta
	x = initial.getX(); // x começa no inicio
	for(int i = 0; i<PARTES; i++) //variamos o X e calculamos um Y, e dai vemos se (x,y) não é obstáculo
	{
		y = m*(x-initial.getX())+initial.getY();
		
		for(unsigned int j=0; j<obstacles.size(); j++) { //para cada obstaculo ve se ele bate na reta
			
			centerx = (obstacles[j].pos.getX());
			centery = (obstacles[j].pos.getY());							
			//equação circunferencia, se da dentro do circulo			 
			if(Point(centerx,centery).getDistance(Point(x,y)) <= radius)
				return true; //obstaculo						
		}
		x = x+varX;
	}
	return false;
}

#pragma message "Mensagem aos desenvolvedores na linha 76."
/* São necessários mesmo esses getters e setters?
 * Só faz sentido fazer esse tipo de coisa quando há um tratamento a mais envolvido. Por exemplo, uma conversão de coordenadas.
 * Nesse caso aqui acho que é uma complicação desnecessária ;)
 */

int GStar::getRadius()
{
	return radius;
}

void GStar::setRadius(int radius)
{
	this->radius = radius;
}

	
//void ordena_obstáculos(point origem, vector obstáculos)
	/*ordena o vetor de obstáculos de acordo com a proximidade da origem
	para saber qual foi o primeiro ponto que bloqueou o caminho*/
	
//point descobre_obstáculo(point origem, point final, vector obstáculos)
	/*retorna qual é o primeiro ponto que está no caminho origem-final
	do robô*/
	
//void cria_pontos(point obstáculo)
	/*cria os 4 pontos ABCD ao redor do obstáculo e armazena numa 
	estrutura*/
	
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
