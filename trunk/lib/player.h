#ifndef __ROBOPET_PLAYER_H__
#define __ROBOPET_PLAYER_H__

#include "movingObject.h"

using RP::MovingObject;
using RP::Player;



/**
 * The RoboPET player abstraction.
 * \ingroup RoboPETLib
 */

class Player: public MovingObject
{
  public:
    enum Role {  };

    Player() { setId(-1); ask_ball = 0;}
    ~Player() {}
	
		
    //----- Getters -----
    inline double 	getCurrentAngle() const { return _current_angle; }
    inline double 	getFutureAngle() const { return _future_angle; }
    inline double 	getDeltaAngle() const { return _delta_angle; }

    inline double 	getAngle() const { return getCurrentAngle(); }

    inline int 		getRole() const { return _role; }

    inline double 	getDisplacementWithBall() const { return  _displacement_with_ball; }

    inline int 		getDriblerIntensity() { return _dribler; }
    inline int 		getKickerIntensity() { return _kicker; }

    inline int 		getId() { return _id; }

    //----- Setters -----
    void 		setCurrentAngle( double newCurrentAngle );
    void 		setFutureAngle( double newFutureAngle );
    void 		setDeltaAngle( double newDeltaAngle );

    inline void setAngle(double a) { setCurrentAngle(a); } 
    
    void 		setRole( int newRole );
    void 		setDisplacementWithBall( double newDisplacementWithBall ) ;

    void 		setDriblerIntensity(int intensity);
    void 		setKickerIntensity(int intensity);

    void 		setId(int id);

    //----- Others -----
    
    /**
     * @return The smallest angle between the current and the future
     */
    double 		calcDeltaAngle();

    inline bool isDribling() { return _dribler > 0; }
    inline bool isKicking() { return _kicker > 0; }
    
    /**
     * Set the future position to be it's current position
     */
	void stay();
	
	/**
	 *	Sets the player future position to be that of the object
	 */
	void follow(MovingObject);
	void goToPoint(Point);

	
	/***
	 *	Asks the object if it is currently at (or very close to) the point
	 *  given as argumment. The threshold for close is 30 MM
	 *  @param p The point to be tested against
	 *  @param threshold The accepted distance offset
	 */
	bool isAt(Point p, int threshold = 30);
	
	/**
     * to be done!!!
     */
    void keepDistanceToBall(double);
    
    
	void keepDistanceToBall(MovingObject, double);
	
    /**
     * Sets the kick intensity to 999
     */
	void 		kick();
	
    /**
     * set the robot's front to be the point p
     * @param p destiny point
     */
	void 		pointTo( Point p );
	
	/**
	 * Check if the robot's front is pointing to "p"
	 * @param p desired point
	 */
	bool 		isPointingTo( Point p );
	
	
    Player& operator=(const Player& other);

    
    //----- Variables -----

	int ask_ball;
			
  private:
    double _current_angle, _future_angle, _delta_angle;
    int _role;
    int _kicker, _dribler, _id;
    double _displacement_with_ball;
};

#endif //__ROBOPET_PLAYER_H__
