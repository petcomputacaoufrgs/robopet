#include "pathplan_player.h"

void PathplanPlayer::setPath(Pathplan *path)
{
	if ( _pathplanner != NULL ) {
		delete _pathplanner;
	}
	
	_pathplanner = path;
}

void PathplanPlayer::setFuturePosition(Point p)
{		
	runPathplanning( getCurrentPosition() , p );

	Player::setFuturePosition(getNextNode());
}

void PathplanPlayer::addObstacle(const MovingObject &m)
{
	_obstacles.push_back(m.getPosition());
}

void PathplanPlayer::runPathplanning(Point from, Point to)
{	
	
	// make it a smart pathplan
	
	_pathplanner->setInitialPos(from);
	_pathplanner->setFinalPos(to);

	_pathplanner->fillEnv(_obstacles);
	_pathplanner->run();
}

Point PathplanPlayer::getNextNode()
{
	// returns the next node in the path
}

