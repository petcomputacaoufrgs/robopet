#ifndef _GSTAR_H_
#define _GSTAR_H_

#include "pathplan.h"

using namespace std;

class GStar : public Pathplan {

	public:
	//---- Constructor and Destructor ----
		GStar();
		~GStar();
		
	//----- Getters & Setters -----
		int  getRadius();
		void setRadius(int radius);
	
	//----- Functions -----
		bool straightIsBlocked(Point initial, Point final);
		
		void run();
		
		Point getPathNode(int pointIndex);
				
		void setInitialPos(Point pos);
		
		void setFinalPos(Point pos);
		
		Point getInitialPos();
		
		Point getFinalPos();

	protected:
	
		int radius;
	
};

#endif

