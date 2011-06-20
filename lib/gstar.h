#ifndef _GSTAR_H_
#define _GSTAR_H_

#include "pathplan.h"
#include <vector>

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

		Obstacle getLastObstacle();
		Obstacle getObstacle(int n);
		int getObstaclesSize();
	
		//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);

	protected:
		//----- Variables -----
		int radius;
		int treshold;
		double secureDistance;
		vector<Obstacle> obst;
		
		//----- Functions -----

		void goToEnd(Point actual, Point final);
		void goToEndA(Point actual, Point final);
		void goToEndB(Point actual, Point final);

		/**
		 * Descricao da funcao.
		 * @return Descricao do valor de retorno.
		 */
		bool straightIsBlocked(Point initial, Point final);
		
		/**
		 * Descricao da funcao.
		 * @return Descricao do valor de retorno.
		 */
		bool straightIsBlockedB();
		
		/**
		 * Descricao da funcao.
		 */
		void makePoints(double m, Point p);
};

#endif

