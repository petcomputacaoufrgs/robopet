#ifndef __ASTAR_H
#define __ASTAR_H

#include <cstdio>
#include <utility>
#include <cmath>
#include <set>
#include <vector>
#include "pathplan.h"

using namespace std;

typedef set<Node> NodeList;

/**
 * Implementation of the A* Pathplanning algorithm
 * \ingroup Pathplan
 */

class AStar : public Pathplan {

	private:
		/**
		*The set of nodes already evaluated
		*/
		NodeList closed_set;
		
		/**
		 * The set of tentative nodes to be evaluated
		 */
		NodeList open_set;

		/**
		 * The map of navigated nodes
		 */
		Node came_from[MAX_X][MAX_Y];

		bool closed[MAX_X][MAX_Y];
		bool open[MAX_X][MAX_Y];

		/**
		 * g equals to the distance from the
		 * source Node to the current evaluated node,
		 * through an optimal path
		 */
		float g[MAX_X][MAX_Y];

		/**
		 * h equals to the estimative distance from the
		 * current evaluated Node to the goal Node (the minimum distance)
		 */ 
		float h[MAX_X][MAX_Y];

		/**
		 * f = g + h
		 */
		float f[MAX_X][MAX_Y];

		void initialize();

	public:
		AStar();
		
		AStar(Node start, Node goal);

		~AStar();

		/**
		 * @return True if node is inlimit
		 */
		bool inLimits(Node y);
		
		/**
		 * @return True if node is a neighbor
		 */
		bool validPosition(Node y);
		
		/**
		 * @return The distance between node a and node b
		 */
		float distance(Node a, Node b);
		
		/**
		 * @return The value g for node x
		 */
		float calcG(Node x);
		
		/**
		 * @return The value h for node x
		 */		
		float calcH(Node x);
	
		/**
		 * @return The value f for node x
		 */
		float calcF(Node x);

		/**
		 * @return The node in openset having the lowest f value
		 */
		Node lowestF();
		
		/**
		 * 
		 */
		Node neighbor(Node x, int i, int j);
		
		/**
		 * Runs A* algorithm
		 */
		void run();
		
		/**
		 * Construct the way of pathplan
		 */
		void reconstructPath();

};

#endif
