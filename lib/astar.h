#ifndef __ASTAR_H
#define __ASTAR_H

#include <cstdio>
#include <utility>
#include <cmath>
#include <set>
#include <vector>
#include "pathplan.h"

using namespace std;

class AStar : public Pathplan {

	private:

		//The set of nodes already evaluated
		set<Node> closed_set;

		//The set of tentative nodes to be evaluated
		set<Node> open_set;

		//The map of navigated nodes
		Node came_from[MAX_X][MAX_Y];

		//g equals to the distance from the
		//source Node to the current evaluated node,
		//through an optimal path
		float g[MAX_X][MAX_Y];

		//h equals to the estimative distance from the
		//current evaluated Node to the goal Node (the minimum distance)
		float h[MAX_X][MAX_Y];

		//f = g + h
		float f[MAX_X][MAX_Y];

		void initialize();

	public:
		AStar();

		AStar(Node start, Node goal);

		~AStar();

		bool inLimits(Node y);

		bool validPosition(Node y);

		float distance(Node a, Node b);

		float calcG(const Node &x);

		float calcH(Node x);

		float calcF(Node x);

		//returns the Node in openset having the lowest f value
		Node lowestF();

		Node neighbor(Node x, int i, int j);

		void run();

		void reconstructPath();

};

#endif
