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
#define EMPTY_STATE (Point(-10, -10))
#define SQR(x) ((x) * (x)) //para Distance


typedef list<Point> Solucao;


class Rrt: public Pathplan
{
	private:
	
	public:
		Rrt() {}
		~Rrt() {}
			
		void run();
	
};

class RRTTree
{
    private:

		void treeToList_recursive(RRTTree *tree,list<Point>*caminho);

    public:

        Point nodo;
        list<RRTTree> filhos;
        RRTTree *pai;

        RRTTree() {pai=NULL;};
        ~RRTTree() {};
        RRTTree(Point param) { nodo = param; };

		list<Point> treeToList(); //transforma arvore em uma lista de nodos
		list<Point> findSolucao(Point goal); //cria uma lista de nodos com o caminho-solucao

		RRTTree operator= (Point param) { return nodo=param; };
};



RRTTree* 	RRTPlan(envType env[][MAX_Y], Point initial, Point goal); //função principal
Point 		ChooseTarget(Point goal);
RRTTree* 	Nearest(RRTTree *tree, Point target);
float 		Distance(Point a, Point b);
Point 		Extend(envType env[][MAX_Y], Point nearest, Point target);
void 		AddNode(RRTTree *nearest, Point extended);
Point 		RandomState();
int 		Collision(envType env[][MAX_Y], Point nearest, Point extended); //há colisão numa linha entre os dois pontos?
void 		nearestState(RRTTree *tree,Point target,RRTTree **nearest);


//funções de teste
void 		printVarreTree(RRTTree *tree,int matrizPrint[][MAX_Y]);
void 		print(RRTTree *tree,Point initial,Point goal,std::list<Point> caminho,envType env[][MAX_Y]);




#endif
