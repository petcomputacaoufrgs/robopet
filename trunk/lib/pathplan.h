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
	FREE, MARKER1, MARKER2, PATH, OBSTACLE
};

enum ppStatusType
{
	SUCCESS, ERROR_TIMELIMIT, ERROR_UNKNOWN, ERROR_UNREACHABLE
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
		Pathplan(Point initialpos, Point finalpos);
		Pathplan();
		~Pathplan();
		void init();

		list<Point> 	pathFull;  //full solution, showing possible partial branches
		list<Point> 	pathFinal; //final solution, for path execution purposes (next point to visit)
		envType 		**env; //generic environment matrix
		ppStatusType 	status;
		
		
		//----- Functions -----
		/** 
		 * Returns a Point from the calculated path with coordinates in mm (milimiters).
		 * 
		 * @param PointIndex index of the Point on the path.
		 * @return The requested Point if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathPointMM(int PointIndex); //returns a specific Point on pathFinal (initialState is 0) in cells units
		
		/** 
		 * Returns a Point from the calculated path with coordinates in Cells unit.
		 * 
		 * @param PointIndex index of the Point on the path.
		 * @return The requested Point if it exists, Point(-1,-1) otherwhise.
		 */
		Point getPathPointCell(int PointIndex); //returns a specific Point on pathFinal (initialState is 0) in mm (milimiters)
		
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
		Point initialpos;
		Point finalpos;
		
		int 	envMatrixX, envMatrixY;
		int  	radius;
		
		//---- Functions ----
		/**
		 * Crates a 'in-field' circle around the position showing whether it's an obstacle or not.
		 */
		void fillEnv_playerBox(int centerx, int centery);
};


#endif
