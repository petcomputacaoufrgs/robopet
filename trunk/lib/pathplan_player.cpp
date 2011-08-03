#include "pathplan_player.h"

void PathplanPlayer::calculateFuturePosition()
{
	itercount++;
	
	// Case 1: run pathplan
	if ( node == PATH_NOT_READY ) {
		pathplan->setInitialPos( getPosition() );
		pathplan->setFinalPos( getFuturePosition() );
		
		cout << "running pathplan..." << endl;
		pathplan->run();
		itercount=0;
		
		if(pathplan->status == SUCCESS)
			node = 0;
		else
			setFuturePosition( getCurrentPosition() );
	}
	// Case 2: pathplan has to be recalculated
	else if ( isAt( pathplan->getFinalPos(), 60 ) || itercount > 10 ) {
		node = PATH_NOT_READY;
		return;
	}
	// Case 3: advance to the next node
	else if ( isAt( getActualNode(), 60 ) ) {
		++node;
	}
	
	if(node != PATH_NOT_READY)
		setFuturePosition( getActualNode() );
}

Point PathplanPlayer::getActualNode()
{
	return pathplan->getPathNode(node);
}

