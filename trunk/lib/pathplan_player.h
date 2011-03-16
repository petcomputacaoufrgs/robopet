#ifndef __PATHPLAN_PLAYER_H__
#define __PATHPLAN_PLAYER_H__

class PathplanPlayer : public Player
{
	public:
		PathplanPlayer(Pathplan *path) : Player();
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
		void fillEnv(const MovingObject &m);

	private:
		Pathplan * _pathplanner;
		int _node;
	
};


#endif /* __PATHPLAN_PLAYER_H__ */

