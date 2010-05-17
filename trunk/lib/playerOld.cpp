#include "jogador.h"
#include "math.h"

#define INDEFINIDO -1

/********************************************************
Construtor b�sico da classe Jogador
********************************************************/
Jogador::Jogador():
     pos(0.0, 0.0), fut(), prev(0.0, 0.0), deslocBola(0.0), thetaAtual(0.0), thetaFuturo(0.0), thetaDesl(0.0) , papel(0), acao(NADA)
{}

/********************************************************  
Construtor da classe jogador
valorX: valor da coordenada x do jogador
valorY: valor da coordenada y do jogador
valorTheta: valor do �ngulo de inclina��o do jogador
********************************************************/
Jogador::Jogador(double valorX, double valorY, double valorTheta)
{
               pos.setXY(valorX, valorY);
               fut.setXY(0, 0);
               setThetaAtual(valorTheta);
               papel = INDEFINIDO;
			   acao = NADA;
}

/********************************************************
M�todo setter da coordenada x do jogador
valorX: novo valor da coordenada x         
********************************************************/
//void Jogador::setX(double valorX)   
//{
//     pos.setX(valorX);
//}

/********************************************************
M�todo getter da coordenada x do jogador
retorno: valor da coordenada x do jogador              
********************************************************/
double Jogador::getX()  
{
       return pos.getX();
}
                 
/********************************************************
M�todo setter da coordenada y do jogador
valorY: novo valor da coordenada y           
********************************************************/
//void Jogador::setY(double valorY)  
//{
//                pos.setY(valorY);
//}

/********************************************************
M�todo getter da coordenada y do jogador
retorno: valor da coordenada y do jogador                
********************************************************/   
double Jogador::getY()  
{
	return pos.getY();
}

/***********************************************
M�todo setter da coordenada x e y do jogador
valorX: novo valor da coordenada x
valorY: novo valor da coordenada y
***********************************************/           
void Jogador::setXY(double valorX, double valorY)
{
    pos.setX(valorX);
    pos.setY(valorY);
}
/************************************************
M�todo setter da estrutura pos
p: nova estrutura pos
************************************************/
void Jogador::setXY(Posicao p)
{
     pos = p;
}

/*************************************************
M�todo getter da coordenada x futura do jogador
retorno: valor da coordenada x futura do jogador   
**************************************************/
double Jogador::getFutX()   
{
       return fut.getX();
}

/**********************************************
M�todo getter da coordenada y futura do jogador
retorno: valor da coordenada y futura do jogador 
**********************************************/
double Jogador::getFutY()   
{
	return fut.getY();
}

/********************************************************
M�todo getter da posi��o futura do jogador
retorno: valor da posi��o futura do jogador 
********************************************************/
Posicao Jogador::getFut()
{
	return fut;
}

/***********************************************
M�todo setter da coordenada x e y futura do jogador
valorX: novo valor da coordenada x futura
valorY: novo valor da coordenada y futura
***********************************************/           
void Jogador::setFutXY(double valorX, double valorY)
{
     fut.setX(valorX);
     fut.setY(valorY);
}

/********************************************************
M�todo setter da coordenada x e y futura do jogador
recebe uma posi�ao para setar
********************************************************/
void Jogador::setFutXY(Posicao futura)
{
     fut = futura;     
}

/********************************************************
M�todo getter da coordenada x anterior do jogador
retorno: valor da coordenada x anterior do jogador   
********************************************************/
double Jogador::getPrevX()
{
	return prev.getX();
}

/********************************************************
M�todo getter da coordenada y anterior do jogador
retorno: valor da coordenada y anterior do jogador 
********************************************************/
double Jogador::getPrevY()
{
	return prev.getY();
}
        
/********************************************************
M�todo setter da coordenada x e y anterior do jogador
valorX: novo valor da coordenada x anterior 
valorY: novo valor da coordenada y anterior
********************************************************/
void Jogador::setPrevXY(double valorX, double valorY)
{
	prev.setX(valorX);
	prev.setY(valorY);
}
    
/********************************************************
M�todo getter da posi��o anterior do jogador
retorno: valor da posi��o anterior do jogador 
********************************************************/
Posicao Jogador::getPrev()
{
	return prev;
}

/********************************************************
M�todo setter da coordenada x e y anterior do jogador
recebe uma posi�ao para setar
********************************************************/
void Jogador::setPrevXY(Posicao anterior)
{
	prev = anterior;
}


/**********************************************
M�todo getter da coordenada x do vetor deslocamento do jogador
retorno: valor da coordenada x do vetor deslocamento do jogador   
**********************************************/
double Jogador::getDeslX()
{
     return desl.getX();
}   

/**********************************************
M�todo getter da coordenada y do vetor deslocamento do jogador
retorno: valor da coordenada y do vetor deslocamento do jogador 
**********************************************/
double Jogador::getDeslY()
{
     return desl.getY();
}


/********************************************************
M�todo getter do vetor deslocamento do jogador
retorno: vetor deslocamento do jogador 
********************************************************/
Vetor Jogador::getDesl()
{
	return desl;
}
        
/********************************************************
M�todo setter da coordenada x e y do vetor deslocamento do jogador
valorX: novo valor da coordenada x do vetor deslocamento
valorY: novo valor da coordenada y do vetor deslocamento
********************************************************/
void Jogador::setDeslXY(double valorX, double valorY)
{
     desl.setXY(valorX, valorY);     
}

/********************************************************
M�todo setter do vetor deslocamento do jogador
********************************************************/
void Jogador::setDesl(Vetor deslocamento)
{
     desl.setXY(deslocamento.getX(), deslocamento.getY());
}

/*******************************************
M�todo getter da estrutura pos
retorno: estrutura pos
*******************************************/
Posicao Jogador::getPos()
{
        return pos;
}  

/********************************************************
M�todo setter da movimenta��o do jogador com a bola
d: novo valor da movimenta��o do jogador com a bola           
********************************************************/
void Jogador::setBolaDesloc(double d)  
{
	deslocBola = d;
}

/********************************************************
M�todo getter da movimenta��o do jogador com a bola
retorno: movimenta��o do jogador com a bola               
********************************************************/   
double Jogador::getBolaDesloc()  
{
       return deslocBola;
}

/********************************************************
m�todo que calcula a movimenta��o do jogador com a bola
********************************************************/
void Jogador::calculaBolaDesloc()
{
	double dist = pos.getDistance(prev);
     
    deslocBola += dist;  
}
/********************************************************
M�todo setter do �ngulo theta atual do jogador
t: novo valor do �ngulo theta      
-> comentar
********************************************************/
void Jogador::setThetaAtual(double t)  
{
	while (t < 0)
		t += 360;
	int parteInteira = (int) t;
	thetaAtual = (parteInteira % 360 + t - parteInteira);
}

/********************************************************
M�todo getter do �ngulo theta do jogador
retorno: valor do �ngulo theta do jogador                
********************************************************/  
double Jogador::getThetaAtual()  
{
       return thetaAtual;
}

/********************************************************
M�todo setter do �ngulo theta do jogador
t: novo valor do �ngulo theta      
-> comentar
********************************************************/
void Jogador::setThetaFuturo(double t)  
{
	while (t < 0)
		t += 360;

	//thetaFuturo = ((int)t) % 360;
	
	int parteInteira = (int) t;
	thetaFuturo = (parteInteira % 360 + t - parteInteira);
}

/********************************************************
M�todo getter do �ngulo theta do jogador
retorno: valor do �ngulo theta do jogador                
********************************************************/  
double Jogador::getThetaFuturo()  
{
       return thetaFuturo;
}
    
/********************************************************
M�todo getter do deslocamento do �ngulo theta do jogador
retorno: valor do deslocamento do �ngulo theta do jogador                
********************************************************/  
double Jogador::getThetaDesl()
{
	return thetaDesl;
}

/********************************************************
M�todo setter do papel do jogador
p: novo papel do jogador
********************************************************/
void Jogador::setPapel(int p) 
{
      papel = p;
}
                
/********************************************************
M�todo getter do papel do jogador
retorno: papel do jogador          
********************************************************/
int Jogador::getPapel()  
{
      return papel;
}

/********************************************************
M�todo setter da acao do jogador
a: nova acao do jogador
********************************************************/
void Jogador::setAcao(int a)
{
	acao = a;
}

/********************************************************
M�todo getter da acao do jogador
retorno: acao do jogador          
********************************************************/
int Jogador::getAcao()
{
	return acao;
}

/********************************************************
M�todo que imprime estado do jogador
********************************************************/
void Jogador::informacao()
{
     cout << "     posicao (" << pos.getX()<< ", " << pos.getY() << ")" << endl;
     cout << "     posicao_futura (" << fut.getX()<< ", " << fut.getY() << ")" << endl;
     cout << "     vetor Deslocamento (" << desl.getX()<< ", " << desl.getY() << ")" << endl;
	 cout << "     modulo vetor deslocamento: " << desl.calculaNorma() << endl;
     cout << "     rotacao " << thetaAtual << endl;
	 cout << "     papel " << papel << endl;

    cout << endl;
          
}
        
/********************************************************
m�todo que calcula o vetor deslocamento do jogador
********************************************************/
void Jogador::calculaDeslocamento()
{
     double x = fut.getX() - pos.getX();
     double y = fut.getY() - pos.getY();
     
     desl.setXY(x, y);    
}

/********************************************************
m�todo que calcula a dist�ncia percorrida pelo jogador desde a �ltima itera��o
********************************************************/
double Jogador::calculaDistPercorrida()
{
	return pos.getDistance(prev);
}

/********************************************************
M�todo que calcula a velocidade do jogador
********************************************************/
double Jogador::calculaVelocidade(double tempo)
{
	if(tempo != 0)
		return calculaDistPercorrida() / tempo;
	else
		return 0;
}

/********************************************************
m�todo que calcula o deslocamento angular do jogador
********************************************************/

#define SIGNUM(x) (((x) > 0) ? (1) : (-1))

void Jogador::calculaDeslocamentoTheta()
{
   double desl = thetaFuturo - thetaAtual;
   if(fabs(desl) > 180) {
		desl = (360 - abs(desl)) * SIGNUM(-desl);
   }
   thetaDesl = desl;
}

/**************************************
Operador de impress�o do jogador
cout
****************************************/
std::ostream& operator<<(std::ostream& out, Jogador j)
{
	char nomesAcoes[4][8] = {"Nada", "Driblar", "Passar", "Chutar" };

	out << "Posicao anterior: " << j.prev << endl;
	out << "Posicao atual: " << j.pos << endl;
	out << "Posicao futura: " << j.fut << endl;
	out << "Vetor deslocamento: " << j.desl << endl;
	out << "Desloc. do jog. com a bola: " << j.deslocBola << endl;
	out << "Theta atual: " << j.thetaAtual << endl;
	out << "Theta futuro: " << j.thetaFuturo << endl;
	out << "Deslocamento theta: " << j.thetaDesl << endl;
	return out << "Acao: " << nomesAcoes[j.acao];
}