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
        
        // posicao para onde o jogador ir� se deslocar no futuro
        Posicao fut;
        
				// estutura que guarda posic��o anterior o jogador
				Posicao prev;

        // vetor deslocamento do jogador
        Vetor desl;

				// quanto o jogador andou com a bola dominada
				double deslocBola;
        
        // theta: �ngulo de inclina��o do rob� com a horizontal (em radianos) 
	    	double thetaAtual;

				double thetaFuturo;

				double thetaDesl;
	    
	    	// papel: papel do jogador no time (atacante, goleiro, etc.)
        int papel;

				// acao do jogador (dribla, passa, chuta, etc.)
				int acao;

				// true se o jogador estiver com a bola dominada e false caso o contr�rio
				//bool bolaDominada;

	public:
        
        Jogador();
        
				/********************************************************
        M�todo getter da coordenada x futura do jogador
        retorno: valor da coordenada x futura do jogador   
        ********************************************************/
        double getFutX();   

        /********************************************************
        M�todo getter da coordenada y futura do jogador
        retorno: valor da coordenada y futura do jogador 
        ********************************************************/
        double getFutY();   
        
        /********************************************************
        M�todo setter da coordenada x e y futura do jogador
        valorX: novo valor da coordenada x futura 
        valorY: novo valor da coordenada y futura
        ********************************************************/
        void setFutXY(double valorX, double valorY);
        
				/********************************************************
        M�todo getter da posi��o futura do jogador
        retorno: valor da posi��o futura do jogador 
        ********************************************************/
				Posicao getFut();

        /********************************************************
        M�todo setter da coordenada x e y futura do jogador
        recebe uma posi�ao para setar
        ********************************************************/
        void setFutXY(Posicao futura);

				/********************************************************
        M�todo getter da coordenada x anterior do jogador
        retorno: valor da coordenada x anterior do jogador   
        ********************************************************/
        double getPrevX();   

        /********************************************************
        M�todo getter da coordenada y anterior do jogador
        retorno: valor da coordenada y anterior do jogador 
        ********************************************************/
        double getPrevY();   
        
        /********************************************************
        M�todo setter da coordenada x e y anterior do jogador
        valorX: novo valor da coordenada x anterior 
        valorY: novo valor da coordenada y anterior
        ********************************************************/
        void setPrevXY(double valorX, double valorY);
        
				/********************************************************
        M�todo getter da posi��o anterior do jogador
        retorno: valor da posi��o anterior do jogador 
        ********************************************************/
				Posicao getPrev();

        /********************************************************
        M�todo setter da coordenada x e y anterior do jogador
        recebe uma posi�ao para setar
        ********************************************************/
        void setPrevXY(Posicao anterior);
        
        /********************************************************
        M�todo getter da coordenada x do vetor deslocamento do jogador
        retorno: valor da coordenada x do vetor deslocamento do jogador   
        ********************************************************/
        double getDeslX();   

        /********************************************************
        M�todo getter da coordenada y do vetor deslocamento do jogador
        retorno: valor da coordenada y do vetor deslocamento do jogador 
        ********************************************************/
        double getDeslY();

				/********************************************************
        M�todo getter do vetor deslocamento do jogador
        retorno: vetor deslocamento do jogador 
        ********************************************************/
				Vetor getDesl();
        
        /********************************************************
        M�todo setter da coordenada x e y do vetor deslocamento do jogador
        valorX: novo valor da coordenada x do vetor deslocamento
        valorY: novo valor da coordenada y do vetor deslocamento
        ********************************************************/
        void setDeslXY(double valorX, double valorY);
        
				void setDesl(Vetor deslocamento);

				/********************************************************
        M�todo setter da movimenta��o do jogador com a bola
        d: novo valor da movimenta��o do jogador com a bola           
        ********************************************************/
        void setBolaDesloc(double d); 
        
        /********************************************************
        M�todo getter da movimenta��o do jogador com a bola
        retorno: movimenta��o do jogador com a bola               
        ********************************************************/  
        double getBolaDesloc();

				/********************************************************
        m�todo que calcula a movimenta��o do jogador com a bola
        ********************************************************/
        void calculaBolaDesloc();
        
        /********************************************************
        M�todo setter do �ngulo theta do jogador
        t: novo valor do �ngulo theta                 
        ********************************************************/
        void setThetaAtual(double t); 
        
        /********************************************************
        M�todo getter do �ngulo theta do jogador
        retorno: valor do �ngulo theta do jogador                
        ********************************************************/  
        double getThetaAtual();
        
				/********************************************************
        M�todo setter do �ngulo theta futuro do jogador
        t: novo valor do �ngulo theta                 
        ********************************************************/
        void setThetaFuturo(double t); 
        
        /********************************************************
        M�todo getter do �ngulo theta futuro do jogador
        retorno: valor do �ngulo theta do jogador                
        ********************************************************/  
        double getThetaFuturo();

        /********************************************************
        M�todo getter do deslocamento do �ngulo theta do jogador
        retorno: valor do deslocamento do �ngulo theta do jogador                
        ********************************************************/  
        double getThetaDesl();

        /********************************************************
        M�todo setter do papel do jogador
        p: novo papel do jogador
        ********************************************************/
        void setPapel(int p);
        
        /********************************************************
        M�todo getter do papel do jogador
        retorno: papel do jogador          
        ********************************************************/
        int getPapel();

        /********************************************************
        M�todo setter da acao do jogador
        a: nova acao do jogador
        ********************************************************/
        void setAcao(int a);
        
        /********************************************************
        M�todo getter da acao do jogador
        retorno: acao do jogador          
        ********************************************************/
        int getAcao();

        /********************************************************
        M�todo que imprime estado do jogador
        ********************************************************/
        void informacao();

				/*******************************************************
				M�todo que calcula a dist�ncia percorrida desde a �ltima itera��o
				********************************************************/
				double calculaDistPercorrida();

				/********************************************************
				M�todo que calcula a velocidade do jogador
				********************************************************/
				double calculaVelocidade(double tempo);

     		/********************************************************
    		m�todo que calcula o vetor deslocamento do jogador
     		********************************************************/
     		void calculaDeslocamento();

        /********************************************************
        m�todo que calcula o deslocamento angular do jogador
        ********************************************************/
        void calculaDeslocamentoTheta();
		
				/**************************************
				Operador de impress�o do jogador
				cout
				****************************************/
				friend std::ostream& operator<<(std::ostream& out, Jogador j);
        
};
    
#endif // _JOGADOR_H_

