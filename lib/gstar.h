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

	protected:
	
		int radius;
	
};

#endif

