#ifndef _PATHPLAN_H_
#define _PATHPLAN_H_

#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>
#include <climits>

#include "constants.h"
#include "player.h"
#include "point.h"

using RP::Point;
using namespace std;


#define CELLS_PER_MM_X  MAX_X / (float) FIELD_WIDTH
#define CELLS_PER_MM_Y  MAX_Y / (float) FIELD_HEIGHT
#define MM_PER_CELLS_X  FIELD_WIDTH / (float) MAX_X
#define MM_PER_CELLS_Y  FIELD_HEIGHT / (float) MAX_Y

#define MM_TO_CELLS_X(x) ((x) * (CELLS_PER_MM_X))
#define MM_TO_CELLS_Y(y) ((y) * (CELLS_PER_MM_Y))

#define CELLS_TO_MM_X(x) ((x) * (MM_PER_CELLS_X))
#define CELLS_TO_MM_Y(y) ((y) * (MM_PER_CELLS_Y))

#define OBSTACULE_RADIUS 5

#define MAX_X 100  //dimensões da matriz que abstrai o ambiente
#define MAX_Y (int)(MAX_X * (FIELD_HEIGHT/FIELD_WIDTH) + 1) //dimensões da matriz que abstrai o ambiente


enum pathplanType
{
	RRT, ASTAR
};

enum envType
{
	FREE, MARKER, NODE, PATH, OBSTACLE
};

class Node {

	public:
		int x;
		int y;

		Node() {}

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


class Pathplan
{
	public:
		//---- Constructor and Destructor ----
		Pathplan(Node initialpos, Node finalpos);
		Pathplan();
		~Pathplan();

		//---- Position on the field (in grid coordinates) ----
		Node initialpos;
		Node finalpos;

		list<Node> pathFull;  //full solution, showing possible partial branches
		list<Node> pathFinal; //final solution, for path execution purposes (next point to visit)
		envType env[MAX_X][MAX_Y]; //generic environment matrix

		//----- Functions -----
		Point getPathNode(int NodeIndex); //returns a specific Node on pathFinal (initialState is 0)
		void fillEnv(vector<RP::Point> positions); //fills the enviroment with positions of the obstacles (currently, only for players)
		int  getRadius();
		void setRadius(int radius);

		/* For debuging purposes.
		 * Prints the actual environment
		 */
		void printEnv();

		virtual void run() {};

		void setInitialPos(Node pos);
		void setFinalPos(Node pos);

		void setInitialPos(Point pos);
		void setFinalPos(Point pos);

	private:
		int radius;

	protected:
		//---- Functions ----
		void fillEnv_playerBox(int centerx, int centery);
};


#endif
