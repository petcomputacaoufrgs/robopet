#include "pathplan_player.h"

void PathplanPlayer::calculateFuturePosition()
{
	// Case 1: no pathplanning has been calculated for this player.
	if ( node == PATH_NOT_READY ) {
		pathplan->setInitialPos( getPosition() );
		pathplan->setFinalPos( getFuturePosition() );
		
		cout << "running pathplan..." << endl;
		pathplan->run();
		if(pathplan->status == SUCCESS)
			node = 0;
	}
	// Case 2: this player has reached it's final goal.
	else if ( isAt( pathplan->getFinalPos(), 60 ) ) {
		node = PATH_NOT_READY;
		return;
	}
	// Case 3: this player has reached the destinated pathplan node.
	else if ( isAt( getActualNode(), 60 ) ) {
		node += 1;
	}
	
	setFuturePosition(getActualNode());
}

Point PathplanPlayer::getActualNode()
{
	return pathplan->getPathNodeMM(node);
}

