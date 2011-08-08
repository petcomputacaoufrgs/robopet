#ifndef _GSTAR_H_
#define _GSTAR_H_

#include "pathplan.h"
#include <vector>
#include <stack>

using namespace std;

typedef struct str_Obstacle
{
	Point center;
	Point p[4];
} Obstacle;

typedef struct str_Path
{
	Point origin;
	Point dest;
	double cost;
} PathCost;

/**
 * Documentation Pending
 * @ingroup Pathplan
 */

class GStar : public Pathplan {

	public:
		//---- Constructor and Destructor ----
		GStar();
		~GStar();
		
		//----- Getters & Setters -----
		Point getInitialPos();
		Point getFinalPos();

		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
		void setRadius(int radius);
		void setTreshold(int treshold);
		void setSecureDistance();
		bool validatePath(Point newGoal, int maxvar);

		Obstacle getObstacle(int n);

		vector<Point> getPointPath();
		vector< vector<Point> > paths;
	
		//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);
		

	protected:
		//----- Variables -----
		int radius;
		int treshold;
		double secureDistance;
		Obstacle *obst;

		//vector<Point> pathGS;
		
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

