#ifndef _GSTAR_H_
#define _GSTAR_H_

#include "pathplan.h"
#include <vector>
#include <stack>
#include <map>

using namespace std;

typedef struct str_Obstacle
{
	Point center;
	Point p[4];
} Obstacle;

/**
 * Documentation Pending
 * @ingroup Pathplan
 */

class GStar : public Pathplan {
	
	//map<double,vector<Points> gsPaths;
	
	public:
		//---- Constructor and Destructor ----
		GStar();
		~GStar();
		
		//----- Getters & Setters -----
		Point getInitialPos();
		Point getFinalPos();

		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
		bool validatePath(Point newGoal, int maxvar);

		Obstacle getObstacle(int n);

		vector<Point> getPointPath();
		vector< vector<Point> > paths;
	
		//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);
		

	protected:
		//----- Variables -----
		Obstacle *obst;		
				
		//----- Functions -----

		/**
		 * Obstruction test based on discretization of the line.
		 * @return True if it's obstructed.
		 * @param obstId Pointer to store the ID of the obstructing obstacle.
		 */
		bool straightIsBlockedDiscrete(Point initial, Point final, int* obstId);
		
		/**
		 * Obstruction test based on algebric calculations with the line equation.
		 * @return True if it's obstructed.
		 * @param obstId Pointer to store the ID of the obstructing obstacle.
		 */
		bool straightIsBlocked(Point p1, Point p2, int* obstId);
		
		/**
		 * Descricao da funcao.
		 */
		void makePoints(int x);
		
		vector<Point> walk(vector<Point> aPath);
		vector<Point> walkA(vector<Point> aPath, Point final, int obstID);
		vector<Point> walkB(vector<Point> aPath, Point final, int obstID);
		bool pointIsInsideRobot(Point p);
		void bestWay();
};

#endif

