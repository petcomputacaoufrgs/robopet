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

class GStar : public Pathplan {

	public:
	//---- Constructor and Destructor ----
		GStar();
		~GStar();
		
	//----- Getters & Setters -----
		void setInitialPos(Point pos);
		void setFinalPos(Point pos);
		Point getInitialPos();
		Point getFinalPos();
		void setRadius(int radius);
		void setTreshold(int treshold);
		void setSecureDistance();
	
	//----- Functions -----
		void run();
		Point getPathNode(int pointIndex);

	protected:
	//----- Variables -----
		int radius;
		int treshold;
		double secureDistance;
		
	//----- Functions -----
		bool straightIsBlocked();
		bool straightIsBlockedB();
		void makePoints();
};

#endif

