#ifndef _RRT_H_
#define _RRT_H_

#include <iostream>
#include <list>

#include "point.h"
#include "constants.h"
#include "pathplan.h"

using RP::Point;
using namespace std;



#define STEP_BY_STEP 0 //yes or no
#define STEPS_DELAY 7

#define EMPTY_STATE (Node(-10, -10))
#define SQR(x) ((x)*(x)) //para Distance

typedef list<Point> Solucao;




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

		list<Node> 	treeToList(); //transforma arvore em uma lista de nodos
		void 		printVarreTree(int matrizPrint[][MAX_Y]);
		void 		print(Node initial,Node goal,std::list<Point> caminho,envType env[][MAX_Y]);

		RRTTree operator= (Node param) { return nodo=param; };
};



class Rrt: public Pathplan
{
	public:
		Rrt( int _directionsToLook=3, int _stepsize=1, double _goalProb=0.5, int _timeLimit=1 ) : directionsToLook(_directionsToLook), stepsize(_stepsize), goalProb(_goalProb), timeLimit(_timeLimit) {}
		~Rrt() {}
		
		int 		directionsToLook;
		int			stepsize;
		double		goalProb;
		int			timeLimit;
		
		void 		run();
		
		
	private:
		RRTTree* 	rrtPlan(Node initial, Node goal); //função principal
		Node 		chooseTarget(Node goal);
		RRTTree* 	findNearest(RRTTree *tree, Node target);
		float 		distance(Node a, Node b);
		Node 		extend(Node nearest, Node target);
		void 		addNode(RRTTree *nearest, Node extended);
		Node 		randomState();
		int 		bresenham(Node stat1, Node stat2);
		int 		collision(Node nearest, Node extended); //há colisão numa linha entre os dois pontos?
		void 		nearestState(RRTTree *tree,Node target,RRTTree **nearest);
		void 		encontraFim(RRTTree *tree,Node goal,RRTTree **fim);
		list<Node>	findSolucao(Node goal, RRTTree *tree); //cria uma lista de nodos com o caminho-solucao
};


#endif
