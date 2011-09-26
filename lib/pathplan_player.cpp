#include "pathplan_player.h"

void PathplanPlayer::calculateFuturePosition()
{
	#define MAXVARIANCE 100
	
	itercount++;
	
	// #1: Pathplan has to be (re)calculated.
	if ( node == PATH_NOT_READY ) {
		pathplan->setInitialPos( getPosition() );
		pathplan->setFinalPos( getPathplanFuturePosition() );
		
		cout << "running pathplan..." << endl;
		pathplan->run();
		itercount=0;
		
		if(pathplan->status == SUCCESS)
			node = 0;
		else
			setFuturePosition( getPathplanFuturePosition() );
	}
	// #2: Check if pathplan has to be recalculated
	else if ( isAt( pathplan->getFinalPos(), MAXVARIANCE ) ||
			  pathplan->getFinalPos() != getPathplanFuturePosition())
	{
		node = PATH_NOT_READY;
		return;
	}
/*	else if (itercount > 1000)
	{
		node = PATH_NOT_READY;
		return;
	}*/
		
	// #3: Advance to the next node
	else if ( isAt( getActualNode(), MAXVARIANCE ) ) {
		++node;
	}
	
	if(node != PATH_NOT_READY)
		setFuturePosition( getActualNode() );
}

Point PathplanPlayer::getActualNode()
{
	return pathplan->getPathNode(node);
}

