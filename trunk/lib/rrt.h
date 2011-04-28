#ifndef _RRT_H_
#define _RRT_H_

#include <iostream>
#include <list>

#include "point.h"
#include "constants.h"
#include "pathplan.h"
#include "utils.h"

using namespace std;
using RP::Point;


#define EMPTY_STATE (Point(-10, -10))
#define SQR(x) ((x)*(x)) //para Distance

typedef vector<Point> Solucao;

/**
 * @ingroup Pathplan
 */

class RRTTree
{
    private:

		/**
		 * Transforms a tree into a list recursively containing the correct path
		 */
		void treeToVector_recursive(RRTTree *tree,vector<Point>*caminho);

    public:

        Point nodo;
        vector<RRTTree> filhos;
        RRTTree *pai;

        RRTTree() {pai=NULL;};
        ~RRTTree() {};
        RRTTree(Point param) { nodo = param; };
        
		/**
		 * Transforms a tree into a vector
		 */
		vector<Point> 	treeToVector(); //transforma arvore em uma lista de nodos

		RRTTree operator= (Point param) { return nodo=param; };
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
		
		vector<Point>	fullPath;

		/**
		 * Runs the Rrt algorithm
		 */
		void 		run();


	private:
		RRTTree 	*tree;
		Point 		initial, goal;

		/**
		 * Generates a path between two points within a time limit.
		 * If the time runs out, the path is set to null
		 */
		RRTTree* 	rrtPlan(); //função principal
		
		/**
		 * Choose whether the direction is towards the objective or to take a random path 
		 */
		Point 		chooseTarget();
		
		/**
		 * Calculates the nearest Point for 'target'
		 * @param target Target Point
		 */
		RRTTree* 	findNearest(Point target);
		
		/**
		 * Calculates the distance between two Points
		 * @param a A Point
		 * @param b Another Point
		 */
		float 		distance(Point a, Point b);
		
		/**
		 * Make a step between Points in the field, selecting the 'shortest' path in a random set of directions
		 * @param nearest The nearest Point
		 * @param target The target Point
		 */
		Point 		extend(Point nearest, Point target);
		
		/**
		 * Creates a new Point and sets it's 'father' to be the nearest Point.
		 * Also, it pushes-back the extended Point to the list of children-Points
		 * @param nearest The nearest Point in the set
		 * @param extended The next Point to follow
		 */
		void 		addPoint(RRTTree *nearest, Point extended);
		
		/**
		 * @return A ordered pair within the field bounds
		 */
		Point 		randomState();
		
		/**
		 * Select points in the field that better aproximates a straight line between two points
		 * @param stat1 Starting Point
		 * @param stat2 Finishing Point
		 */
		int 		bresenham(Point stat1, Point stat2);
		
		/**
		 * Guarantee that the line between the two Points can be walked upon
		 * @param nearest The nearest Point
		 * @param extended The extended Point
		 */
		int 		collision(Point nearest, Point extended);
		
		/**
		 * Finds the nearest Point of the tree to the target
		 * @param tree The tree to be searched on
		 * @param target The target point
		 * @param nearest Double pointer to store the nearest Point
		 */
		void 		nearestState(RRTTree *tree,Point target,RRTTree **nearest);
		
		/**
		 * Find the end of a tree
		 * @param tree The tree to be searched on
		 * @param goal The ending Point
		 * @param fim A pointer 
		 */
		void 		encontraFim(RRTTree *tree,Point goal,RRTTree **fim);
		
		/**
		 * Creates a list with the path-solution Points
		 */
		vector<Point>	findSolution();
};


#endif
