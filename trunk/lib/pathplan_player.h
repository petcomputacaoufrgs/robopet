#pragma once


#include "player.h"
#include "pathplan.h"

#define PATH_NOT_READY -1

/**
 * The Player abstraction for using pathplanning.
 * \ingroup RoboPETLib
 * */

class PathplanPlayer : public Player
{
	public:
		PathplanPlayer() : Player(), pathplan(NULL), node(PATH_NOT_READY) {};
		~PathplanPlayer() {};

		Pathplan	*pathplan;
		int 		node;
			
		void 		calculateFuturePosition();
		Point 		getActualNode();

	private:	
		int var;
};

