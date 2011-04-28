#pragma once


#include "player.h"
#include "pathplan.h"

#define PATH_NOT_READY -1

class PathplanPlayer : public Player
{
	public:
		PathplanPlayer() : Player(), pathplan(NULL), node(PATH_NOT_READY) {};
		~PathplanPlayer() {};

		Pathplan	*pathplan;
		int 		node;
			
		void 		iteratePathplan();
		Point 		getActualNode();

	private:	
	
};

