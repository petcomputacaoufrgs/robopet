#ifndef __ASTAR_H
#define __ASTAR_H

#include <cstdio>
#include <utility>
#include <cmath>
#include <set>
#include <vector>
#include "pathplan.h"

typedef RP::Point node;

using namespace std;

class AStar : Pathplan {

	private:

		//The set of nodes already evaluated
		set<node> closed_set;

		//The set of tentative nodes to be evaluated
		set<node> open_set;

		//The map of navigated nodes
		node came_from[MAX_X][MAX_Y];

		//g equals to the distance from the
		//source node to the current evaluated node,
		//through an optimal path
		float g[MAX_X][MAX_Y];

		//h equals to the estimative distance from the
		//current evaluated node to the goal node (the minimum distance)
		float h[MAX_X][MAX_Y];

		//f = g + h
		float f[MAX_X][MAX_Y];

	public:

		AStar(node start, node goal);

		~AStar();

		bool inLimits(node y);

		float distance(node a, node b);

		float calcG(node x);

		float calcH(node x);

		float calcF(node x);

		//returns the node in openset having the lowest f value
		node lowestF();

		node neighbor(node x, int i, int j);

		void run();

		void reconstructPath();

};

#endif
