#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include "posicao.h"
#include "vetor.h"
#include "auxiliares.h"

#define MENOR_ROTACAO 1

class Player : public FieldObject
{
    private:
        // estrutura de dados para guardar a posicao do jogador no campo..    
        Posicao pos;
        
        // posicao para onde o jogador irá se deslocar no futuro
        Posicao fut;
        
				// estutura que guarda posicção anterior o jogador
				Posicao prev;

        // vetor deslocamento do jogador
        Vetor desl;

				// quanto o jogador andou com a bola dominada
				double deslocBola;
        
        // theta: ângulo de inclinação do robô com a horizontal (em radianos) 
	    	double thetaAtual;

				double thetaFuturo;

				double thetaDesl;
	    
	    	// papel: papel do jogador no time (atacante, goleiro, etc.)
        int papel;

				// acao do jogador (dribla, passa, chuta, etc.)
				int acao;

				// true se o jogador estiver com a bola dominada e false caso o contrário
				//bool bolaDominada;

	public:
        
        Jogador();
        
				/********************************************************
        Método getter da coordenada x futura do jogador
        retorno: valor da coordenada x futura do jogador   
        ********************************************************/
        double getFutX();   

        /********************************************************
        Método getter da coordenada y futura do jogador
        retorno: valor da coordenada y futura do jogador 
        ********************************************************/
        double getFutY();   
        
        /********************************************************
        Método setter da coordenada x e y futura do jogador
        valorX: novo valor da coordenada x futura 
        valorY: novo valor da coordenada y futura
        ********************************************************/
        void setFutXY(double valorX, double valorY);
        
				/********************************************************
        Método getter da posição futura do jogador
        retorno: valor da posição futura do jogador 
        ********************************************************/
				Posicao getFut();

        /********************************************************
        Método setter da coordenada x e y futura do jogador
        recebe uma posiçao para setar
        ********************************************************/
        void setFutXY(Posicao futura);

				/********************************************************
        Método getter da coordenada x anterior do jogador
        retorno: valor da coordenada x anterior do jogador   
        ********************************************************/
        double getPrevX();   

        /********************************************************
        Método getter da coordenada y anterior do jogador
        retorno: valor da coordenada y anterior do jogador 
        ********************************************************/
        double getPrevY();   
        
        /********************************************************
        Método setter da coordenada x e y anterior do jogador
        valorX: novo valor da coordenada x anterior 
        valorY: novo valor da coordenada y anterior
        ********************************************************/
        void setPrevXY(double valorX, double valorY);
        
				/********************************************************
        Método getter da posição anterior do jogador
        retorno: valor da posição anterior do jogador 
        ********************************************************/
				Posicao getPrev();

        /********************************************************
        Método setter da coordenada x e y anterior do jogador
        recebe uma posiçao para setar
        ********************************************************/
        void setPrevXY(Posicao anterior);
        
        /********************************************************
        Método getter da coordenada x do vetor deslocamento do jogador
        retorno: valor da coordenada x do vetor deslocamento do jogador   
        ********************************************************/
        double getDeslX();   

        /********************************************************
        Método getter da coordenada y do vetor deslocamento do jogador
        retorno: valor da coordenada y do vetor deslocamento do jogador 
        ********************************************************/
        double getDeslY();

				/********************************************************
        Método getter do vetor deslocamento do jogador
        retorno: vetor deslocamento do jogador 
        ********************************************************/
				Vetor getDesl();
        
        /********************************************************
        Método setter da coordenada x e y do vetor deslocamento do jogador
        valorX: novo valor da coordenada x do vetor deslocamento
        valorY: novo valor da coordenada y do vetor deslocamento
        ********************************************************/
        void setDeslXY(double valorX, double valorY);
        
				void setDesl(Vetor deslocamento);

				/********************************************************
        Método setter da movimentação do jogador com a bola
        d: novo valor da movimentação do jogador com a bola           
        ********************************************************/
        void setBolaDesloc(double d); 
        
        /********************************************************
        Método getter da movimentação do jogador com a bola
        retorno: movimentação do jogador com a bola               
        ********************************************************/  
        double getBolaDesloc();

				/********************************************************
        método que calcula a movimentação do jogador com a bola
        ********************************************************/
        void calculaBolaDesloc();
        
        /********************************************************
        Método setter do ângulo theta do jogador
        t: novo valor do ângulo theta                 
        ********************************************************/
        void setThetaAtual(double t); 
        
        /********************************************************
        Método getter do ângulo theta do jogador
        retorno: valor do ângulo theta do jogador                
        ********************************************************/  
        double getThetaAtual();
        
				/********************************************************
        Método setter do ângulo theta futuro do jogador
        t: novo valor do ângulo theta                 
        ********************************************************/
        void setThetaFuturo(double t); 
        
        /********************************************************
        Método getter do ângulo theta futuro do jogador
        retorno: valor do ângulo theta do jogador                
        ********************************************************/  
        double getThetaFuturo();

        /********************************************************
        Método getter do deslocamento do ângulo theta do jogador
        retorno: valor do deslocamento do ângulo theta do jogador                
        ********************************************************/  
        double getThetaDesl();

        /********************************************************
        Método setter do papel do jogador
        p: novo papel do jogador
        ********************************************************/
        void setPapel(int p);
        
        /********************************************************
        Método getter do papel do jogador
        retorno: papel do jogador          
        ********************************************************/
        int getPapel();

        /********************************************************
        Método setter da acao do jogador
        a: nova acao do jogador
        ********************************************************/
        void setAcao(int a);
        
        /********************************************************
        Método getter da acao do jogador
        retorno: acao do jogador          
        ********************************************************/
        int getAcao();

        /********************************************************
        Método que imprime estado do jogador
        ********************************************************/
        void informacao();

				/*******************************************************
				Método que calcula a distância percorrida desde a última iteração
				********************************************************/
				double calculaDistPercorrida();

				/********************************************************
				Método que calcula a velocidade do jogador
				********************************************************/
				double calculaVelocidade(double tempo);

     		/********************************************************
    		método que calcula o vetor deslocamento do jogador
     		********************************************************/
     		void calculaDeslocamento();

        /********************************************************
        método que calcula o deslocamento angular do jogador
        ********************************************************/
        void calculaDeslocamentoTheta();
		
				/**************************************
				Operador de impressão do jogador
				cout
				****************************************/
				friend std::ostream& operator<<(std::ostream& out, Jogador j);
        
};
    
#endif // _JOGADOR_H_

