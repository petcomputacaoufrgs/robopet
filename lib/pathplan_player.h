#pragma once


#include "player.h"
#include "pathplan.h"

#define PATH_NOT_READY -1

class PathplanPlayer : public Player
{
	public:
		PathplanPlayer() : Player() { node = PATH_NOT_READY; pathplan=NULL; };
		~PathplanPlayer() {};

		Pathplan	*pathplan;
		int 		node;
			
		void 		iteratePathplan();
		Point 		getActualNode();

	private:	
	
};

