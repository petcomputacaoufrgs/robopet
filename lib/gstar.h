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

typedef struct str_StackPoint
{
	int obstacle_id;
	int p;
} StackPoint;

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

		Obstacle getObstacle(int n);

		vector<Point> getPointPath();
	
		//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);

	protected:
		//----- Variables -----
		int radius;
		int treshold;
		double secureDistance;
		Obstacle *obst;
		stack<StackPoint> points;
		stack<StackPoint> actualPoints;

		//vector<Point> pathGS;
		
		//----- Functions -----

		void calcCost(PathCost *p);

		void goToEnd();

		/**
		 * Descricao da funcao.
		 * @return Descricao do valor de retorno.
		 */
		bool straightIsBlocked(Point initial, Point final, StackPoint* temp);
		
		/**
		 * Descricao da funcao.
		 * @return Descricao do valor de retorno.
		 */
		bool straightIsBlockedB();
		
		/**
		 * Descricao da funcao.
		 */
		void makePoints(int x);
};

#endif

