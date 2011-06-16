#ifndef _GSTAR_H_
#define _GSTAR_H_

#include "pathplan.h"

using namespace std;

struct Vertexes
{
	Point center;
	Point A;
	Point B;
	Point C;
	Point D;
};

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

		struct Vertexes getPoints();
	
		//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);

	protected:
		//----- Variables -----
		int radius;
		int treshold;
		double secureDistance;
		struct Vertexes vert;
		
		//----- Functions -----
		/**
		 * Descricao da funcao.
		 * @return Descricao do valor de retorno.
		 */
		bool straightIsBlocked();
		
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

