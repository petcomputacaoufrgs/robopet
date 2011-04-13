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

enum envType
{
	FREE, MARKER1, MARKER2, NODE, PATH, OBSTACLE
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

		list<Node> pathFull;  //full solution, showing possible partial branches
		list<Node> pathFinal; //final solution, for path execution purposes (next point to visit)
		envType **env; //generic environment matrix
		
		//----- Functions -----
		/** 
		 * Returns a node from the calculated path with coordinates in mm (milimiters).
		 * 
		 * @param NodeIndex index of the node on the path.
		 * @return The requested node if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathNodeMM(int NodeIndex); //returns a specific Node on pathFinal (initialState is 0) in cells units
		
		/** 
		 * Returns a node from the calculated path with coordinates in Cells unit.
		 * 
		 * @param NodeIndex index of the node on the path.
		 * @return The requested node if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathNodeCell(int NodeIndex); //returns a specific Node on pathFinal (initialState is 0) in mm (milimiters)
		
		/** 
		 * Fills the enviroment with positions of the obstacles.
		 * 
		 * @param positions positions, in mm, of the obstacules.
		*/
		void fillEnv(vector<RP::Point> positions); //fills the enviroment with positions of the obstacles (currently, only for players)
		
		/** 
		 * Returns the value used as radius (unit: cells) for obstacules in the environment matrix.
		 */
		int  getRadius();
		
		/** 
		 * Sets the value used as radius (unit: cells) for obstacules in the environment matrix.
		 */
		void setRadius(int radius);
		
		/** 
		 * Sets the dimensions (unit: cells) of the environment matrix.
		 * 
		 * @param x horizontal dimension
		 * @param y vertical dimension
		 */
		void setEnvXY( int x, int y );
		
		/** 
		 * Returns the horizontal dimension (unit: cells) of the environment matrix.
		 */
		int getEnvMatrixX();
		
		/** 
		 * Returns the vertical dimension (unit: cells) of the environment matrix.
		 */
		int getEnvMatrixY();
		
		/** Used for debugging purposes.
		 * Prints the actual environment
		 */
		void printEnv();
		
		/** Used for debugging purposes.
		 * Prints the actual environment with the calculated path
		 */
		void printPathplan();
		
		/**
		 * Creates the path using a given algorithm.
		 */
		virtual void run() {};

		/** 
		 * Sets the initial position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setInitialPos(Node pos);
		
		/** 
		 * Sets the final position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setFinalPos(Node pos);

		/** 
		 * Sets the initial position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setInitialPos(Point pos);
		
		/** 
		 * Sets the final position of the pathplan to be runned.
		 * 
		 * @param pos Position in mm (milimiters).
		 */
		void setFinalPos(Point pos);
		
		/** 
		 * Returns the initial position (unit: mm) of the pathplan.
		 */
		Point getInitialPos();
		
		/** 
		 * Returns the final position (unit: mm) of the pathplan.
		 */
		Point getFinalPos();
		
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
		//---- Position on the field (in grid coordinates) ----
		Node initialpos;
		Node finalpos;
		
		int 	envMatrixX, envMatrixY;
		int  	radius;
		
		//---- Functions ----
		/**
		 * Crates a 'in-field' circle around the position showing whether it's an obstacle or not.
		 */
		void fillEnv_playerBox(int centerx, int centery);
};


#endif
