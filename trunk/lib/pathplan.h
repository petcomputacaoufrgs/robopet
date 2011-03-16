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


#define OBSTACULE_RADIUS 5

#define ENV_MATRIX_SIZE_X 60  //dimensão x da matriz que abstrai o ambiente

/**
 * \defgroup Pathplan Pathplan
 * \ingroup Pathplan
 */

enum pathplanType
{
	RRT, ASTAR
};

enum envType
{
	FREE, MARKER, NODE, PATH, OBSTACLE
};

/**
 * Node
 * Documentation Pending
 * \ingroup Pathplan
 */

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

/**
 * Abstract class defining a framework for pathplanning code
 * Further Documentation Pending
 * \ingroup Pathplan
 */

class Pathplan
{
	public:
		//---- Constructor and Destructor ----
		Pathplan(Node initialpos, Node finalpos);
		Pathplan();
		~Pathplan();
		void init();

		//---- Position on the field (in grid coordinates) ----
		Node initialpos;
		Node finalpos;

		list<Node> pathFull;  //full solution, showing possible partial branches
		list<Node> pathFinal; //final solution, for path execution purposes (next point to visit)
		envType **env; //generic environment matrix

		//----- Functions -----
		Point getPathNode(int NodeIndex); //returns a specific Node on pathFinal (initialState is 0)
		
		/** 
		 * Fills the enviroment with positions of the obstacles (currently, ball and players)
		*/
		void fillEnv(vector<RP::Point> positions); //fills the enviroment with positions of the obstacles (currently, only for players)
		int  getRadius();
		void setRadius(int radius);
		
		int 	envMatrixX, envMatrixY;

		/** Used for debugging purposes.
		 * Prints the actual environment
		 */
		void printEnv();
		
		/**
		 * Creates the path using a given algorithm.
		 */
		virtual void run() {};

		void setInitialPos(Node pos);
		void setFinalPos(Node pos);

		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
		
		// CONVERSION FUNCTIONS
		double CELLS_PER_MM_X() { return envMatrixX / (float) FIELD_WIDTH; }
		double CELLS_PER_MM_Y() { return envMatrixY / (float) FIELD_HEIGHT; }
		double MM_PER_CELLS_X() { return FIELD_WIDTH / (float) envMatrixX; }
		double MM_PER_CELLS_Y() { return FIELD_HEIGHT / (float) envMatrixY; }

		double MM_TO_CELLS_X(double x) { return x * (CELLS_PER_MM_X()); }
		double MM_TO_CELLS_Y(double y) { return y * (CELLS_PER_MM_Y()); }

		double CELLS_TO_MM_X(double x) { return x * (MM_PER_CELLS_X()); }
		double CELLS_TO_MM_Y(double y) { return y * (MM_PER_CELLS_Y()); }

	
	private:

	protected:
		int  	radius;
		
		//---- Functions ----
		/**
		 * Crates a 'in-field' circle around the position showing whether it's an obstacle or not.
		 */
		void fillEnv_playerBox(int centerx, int centery);
};


#endif
