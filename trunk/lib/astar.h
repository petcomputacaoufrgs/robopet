#ifndef __ASTAR_H
#define __ASTAR_H

#include <cstdio>
#include <utility>
#include <cmath>
#include <set>
#include <vector>
#include "pathplan.h"
#include "discretePathplan.h"

using namespace std;

/**
 * Node class.
 * \todo Why not create a Point class to work with integers?
 * \ingroup Pathplan
 */

class Node {

	public:
		int x;
		int y;

		Node() { x=0; y=0; }

		Node(int x, int y) {
			this->x = x;
			this->y = y;
		}

		bool operator==(const Node &other) const {
			return ((other.x == x) && (other.y == y));
		}

		bool operator==(const Point &other) const {
			return ((other.getX() == x) && (other.getY() == y));
		}

		bool operator!=(const Node &other) const {
			return ((other.x != x) || (other.y != y));
		}

		bool operator<(const Node &other) const {
			return ((this->x < other.x) ||
					((this->x == other.x) && (this->y < other.y)));
		}

		int getX() { return x; }

		int getY() { return y; }

		void setX(int x) { this->x = x; }

		void setY(int y) { this->y = y;}

};

typedef set<Node> NodeList;

/**
 * Implementation of the A* Pathplanning algorithm
 * \ingroup Pathplan
 */

class AStar : public DiscretePathplan {

	public:
		AStar();
		
		AStar(Node start, Node goal);

		~AStar();
		
		void init();

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
		 * @return The new node coordinates incremented with i and j, respectively
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
		
	private:
		Node nodeinitialpos, nodefinalpos;
		
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
		Node** came_from;

		bool** closed;
		bool** open;

		/**
		 * g equals to the distance from the
		 * source Node to the current evaluated node,
		 * through an optimal path
		 */
		float** g;

		/**
		 * h equals to the estimative distance from the
		 * current evaluated Node to the goal Node (the minimum distance)
		 */ 
		float** h;

		/**
		 * f = g + h
		 */
		float** f;

		void initialize();
};
#endif
