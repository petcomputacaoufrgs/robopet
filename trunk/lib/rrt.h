#ifndef _RRT_H_
#define _RRT_H_

#include<iostream>
#include<list>

#include "point.h"
#include "constants.h"

//Constantes Variáveis
#define DIRECTIONS_TO_LOOK 3 //para extend, deve estar em {0, 1, ..., 8}
#define MAX_STEPSIZE 1

#define THRESHOLD MAX_STEPSIZE
#define GOAL_PROB 0.5

#define STEP_BY_STEP 0 //yes or no
#define STEPS_DELAY 7

//constantes
#define EMPTY_STATE (state(-10, -10))
#define SQR(x) ((x) * (x)) //para Distance


using RP::Point;
using namespace std;


enum{
	LIVRE     = 0,
	OBSTACULO = 1,
	MARCADOR  = 2,
	NODO      = 3,
	CAMINHO   = 4
	};


//class state
//{
//    public:
//        int x, y;
//
//        state(int a = -1, int b = -1) {
//            x = a;
//            y = b;
//        }
//
//        bool operator!= (state param) {
//            return x!=param.x || y!=param.y;
//        }
//        bool operator== (state param) {
//            return x==param.x && y==param.y;
//        }
//
//};


typedef Point state;
typedef list<state> Solucao;


class RRTTree
{
    private:

		void treeToList_recursive(RRTTree *tree,list<state>*caminho);

    public:

        state nodo;
        list<RRTTree> filhos;
        RRTTree *pai;

        RRTTree() {pai=NULL;};
        ~RRTTree() {};
        RRTTree(state param) { nodo = param; };

		list<state> treeToList(); //transforma rvore em uma lista de nodos
		list<state> findSolucao(state goal); //cria uma lista de nodos com o caminho-solu��o

		RRTTree operator= (state param) { return nodo=param; };
};



RRTTree* RRTPlan(int env[][MAX_Y], state initial, state goal); //função principal
state ChooseTarget(state goal);
RRTTree* Nearest(RRTTree *tree, state target);
float Distance(state a, state b);
state Extend(int env[][MAX_Y], state nearest, state target);
void AddNode(RRTTree *nearest, state extended);
state RandomState();
int Collision(int env[][MAX_Y], state nearest, state extended); //há colisão numa linha entre os dois pontos?
void nearestState(RRTTree *tree,state target,RRTTree **nearest);


//funções de teste
void printVarreTree(RRTTree *tree,int matrizPrint[][MAX_Y]);
void print(RRTTree *tree,state initial,state goal,std::list<state> caminho,int env[][MAX_Y]);




#endif
