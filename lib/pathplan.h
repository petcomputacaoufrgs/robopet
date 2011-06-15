#pragma once


#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <climits>

#include "constants.h"
#include "player.h"
#include "point.h"

using RP::Point;
using namespace std;


#define OBSTACULE_RADIUS 5

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
	NOTHING, SUCCESS, ERROR_TIMELIMIT, ERROR_UNKNOWN, ERROR_UNREACHABLE
};

enum obstacleType
{
	BALL, ROBOT
};

struct ppObstacle
{
	Point pos;
	obstacleType type;
	
	ppObstacle(Point _pos, obstacleType _type) : pos(_pos), type(_type) {}
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
		Pathplan();
		~Pathplan();

		vector<Point> 		path;
		vector<ppObstacle>	obstacles;
		ppStatusType 		status;
		
		
		//----- Functions -----
		/**
		 * Runs the pathplanning.
		 */
		virtual void run() = 0;
		
		/**
		 * Getter of a specific node of a calculated path.
		 * @param pointIndex Index of the node on the path. Starts on 0 (zero).
		 * @return The asked point in mm (milimeters).
		 */
		virtual Point getPathNode(int pointIndex) = 0;
		
		/**
		 * Setter of the initial position of the pathplan to be run.
		 * @param pos Point in mm (milimeters).
		 */
		virtual void setInitialPos(Point pos) = 0;
		
		/**
		 * Setter of the final position of the pathplan to be run.
		 * @param pos Point in mm (milimeters).
		 */
		virtual void setFinalPos(Point pos) = 0;
		
		/**
		 * Getter of the initial position of the pathplan to be run.
		 * @return Point in mm (milimeters).
		 */
		virtual Point getInitialPos() = 0;
		
		/**
		 * Getter of the final position of the pathplan to be run.
		 * @return Point in mm (milimeters).
		 */
		virtual Point getFinalPos() = 0;
		
		
	protected:
	
		Point initialpos;
		Point finalpos;
};
