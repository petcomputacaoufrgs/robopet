#ifndef __PATHPLAN_PLAYER_H__
#define __PATHPLAN_PLAYER_H__

#include "player.h"
#include "pathplan.h"

class PathplanPlayer : public Player
{
	public:
		PathplanPlayer(Pathplan *path) : Player() {};
		~PathplanPlayer();

		/**
		 *	Sets a new algorithm to be used as the pathplanning
		 *  @param path A pointer to a new pathplanning object
		 */
		void setPath(Pathplan *path);

		/**
		 *	Sets the desired future position and triggers the pathplanning. Most
		 *	likely the actual future position will vary.
		 * 
		 */
		void setFuturePosition(Point p);

		/**
		 *	Receives an object and inserts it in the pathplann
		 *  @param m The object
		 */
		void addObstacle(const MovingObject &m);

	private:
		Pathplan *_pathplanner;
		// actually there's no need to store all the positions
		// again in every robot, maybe we could add some references 
		// here and there, but meh... let's wait
		vector<Point> _obstacles;
		int _node;
		
		void runPathplanning(Point from, Point to);
		Point getNextNode();
	
};


#endif /* __PATHPLAN_PLAYER_H__ */

