#ifndef _RRT_H_
#define _RRT_H_

#include <iostream>
#include <list>

#include "point.h"
#include "constants.h"
#include "pathplan.h"

using RP::Point;
using namespace std;

//Constantes Variáveis
#define DIRECTIONS_TO_LOOK 3 //para extend, deve estar em {0, 1, ..., 8}
#define MAX_STEPSIZE 1

#define THRESHOLD MAX_STEPSIZE
#define GOAL_PROB 0.5

#define STEP_BY_STEP 0 //yes or no
#define STEPS_DELAY 7

//constantes
#define EMPTY_STATE (Node(-10, -10))
#define SQR(x) ((x) * (x)) //para Distance

typedef list<Point> Solucao;


class Rrt: public Pathplan
{

	private:

	public:
		Rrt() { }
		~Rrt() {}

		void run();

};

class RRTTree
{
    private:

		void treeToList_recursive(RRTTree *tree,list<Node>*caminho);


    public:

        Node nodo;
        list<RRTTree> filhos;
        RRTTree *pai;

        RRTTree() {pai=NULL;};
        ~RRTTree() {};
        RRTTree(Node param) { nodo = param; };

		list<Node> treeToList(); //transforma arvore em uma lista de nodos
		list<Node> findSolucao(Node goal); //cria uma lista de nodos com o caminho-solucao

		RRTTree operator= (Node param) { return nodo=param; };
};



RRTTree* 	RRTPlan(envType env[][MAX_Y], Node initial, Node goal); //função principal
Node 		ChooseTarget(Node goal);
RRTTree* 	Nearest(RRTTree *tree, Node target);
float 		Distance(Node a, Node b);
Node 		Extend(envType env[][MAX_Y], Node nearest, Node target);
void 		AddNode(RRTTree *nearest, Node extended);
Node 		RandomState();
int 		Collision(envType env[][MAX_Y], Node nearest, Node extended); //há colisão numa linha entre os dois pontos?
void 		nearestState(RRTTree *tree,Node target,RRTTree **nearest);


//funções de teste
void 		printVarreTree(RRTTree *tree,int matrizPrint[][MAX_Y]);
void 		print(RRTTree *tree,Node initial,Node goal,std::list<Point> caminho,envType env[][MAX_Y]);




#endif
