#ifndef _RRT_H_
#define _RRT_H_

#include <iostream>
#include <list>

#include "point.h"
#include "constants.h"
#include "pathplan.h"

using RP::Point;
using namespace std;


#define EMPTY_STATE (Node(-10, -10))
#define SQR(x) ((x)*(x)) //para Distance

typedef list<Point> Solucao;

/**
 * @ingroup Pathplan
 */

class RRTTree
{
    private:

		/**
		 * Transforms a tree into a list recursively containing the correct path
		 */
		void treeToList_recursive(RRTTree *tree,list<Node>*caminho);

    public:

        Node nodo;
        list<RRTTree> filhos;
        RRTTree *pai;

        RRTTree() {pai=NULL;};
        ~RRTTree() {};
        RRTTree(Node param) { nodo = param; };
        
		/**
		 * Transforms a tree into a list
		 */
		list<Node> 	treeToList(); //transforma arvore em uma lista de nodos

		RRTTree operator= (Node param) { return nodo=param; };
};

/**
 * Documentation Pending
 * @ingroup Pathplan
 */

class Rrt: public Pathplan
{
	public:
		Rrt( int _directionsToLook=3, int _stepsize=1, double _goalProb=0.5, int _timeLimit=1 ) : directionsToLook(_directionsToLook), stepsize(_stepsize), goalProb(_goalProb), timeLimit(_timeLimit) {}
		~Rrt() {}

		int 		directionsToLook;
		int			stepsize;
		double		goalProb;
		int			timeLimit;

		/**
		 * Runs the Rrt algorithm
		 */
		void 		run();


	private:
		RRTTree 	*tree;
		Node 		initial, goal;

		/**
		 * Generates a path between two points within a time limit.
		 * If the time runs out, the path is set to null
		 */
		RRTTree* 	rrtPlan(); //função principal
		
		/**
		 * Choose whether the direction is towards the objective or to take a random path 
		 */
		Node 		chooseTarget();
		
		/**
		 * Calculates the nearest node for 'target'
		 * @param target Target node
		 */
		RRTTree* 	findNearest(Node target);
		
		/**
		 * Calculates the distance between two nodes
		 * @param a A node
		 * @param b Another node
		 */
		float 		distance(Node a, Node b);
		
		/**
		 * Make a step between nodes in the field, selecting the 'shortest' path in a random set of directions
		 * @param nearest The nearest node
		 * @param target The target node
		 */
		Node 		extend(Node nearest, Node target);
		
		/**
		 * Creates a new node and sets it's 'father' to be the nearest node.
		 * Also, it pushes-back the extended node to the list of children-nodes
		 * @param nearest The nearest node in the set
		 * @param extended The next node to follow
		 */
		void 		addNode(RRTTree *nearest, Node extended);
		
		/**
		 * @return A ordered pair within the field bounds
		 */
		Node 		randomState();
		
		/**
		 * Select points in the field that better aproximates a straight line between two points
		 * @param stat1 Starting node
		 * @param stat2 Finishing node
		 */
		int 		bresenham(Node stat1, Node stat2);
		
		/**
		 * Guarantee that a line is inside the field limits
		 * @param nearest The nearest node
		 * @param extended The extended node
		 */
		int 		collision(Node nearest, Node extended); //há colisão numa linha entre os dois pontos?
		
		/**
		 * comment pending
		 */
		void 		nearestState(RRTTree *tree,Node target,RRTTree **nearest);
		
		/**
		 * Find the end of a tree
		 * @param tree The tree to be searched
		 * @param goal The goal node
		 * @param fim A pointer 
		 */
		void 		encontraFim(RRTTree *tree,Node goal,RRTTree **fim);
		
		/**
		 * Creates a list with the path-solution nodes
		 */
		list<Node>	findSolution(); //cria uma lista de nodos com o caminho-solucao
		
		/**
		 * Sets, in the field, all the tree-solution nodes to be a NODE type
		 * @param tree The tree to be iterated
		 * @param matrizPrint The matriz in which the tree nodes will be marked
		 */
		void 		printVarreTree(RRTTree *tree, int matrizPrint[][MAX_Y]);
		
		/**
		 * Fill the field with players, ball, nodes and the correct path to follow.
		 * Do that setting a different type of node for different in-field 'objects'
		 */
		void 		printResult();
};


#endif
