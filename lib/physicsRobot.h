#ifndef __ROBOPET_PHYSICS_ROBOT_H__
#define __ROBOPET_PHYSICS_ROBOT_H__

#include "vector.h"

/** Physic state of a robot 
 * \ingroup RoboPETLib
 */
	
class PhysicsRobot {

private:

	int _angle;

public:

	/**
	 * Rotation sense 
	 */
	enum {
		CW = 1,
		CCW = -1
	};

	PhysicsRobot(){}
	PhysicsRobot(int angle);

   /** 
   * @return The new physical state after moving in the directon of angle 'ang' [0,360),
   * possibly rotating (rotate) in sense 's' (CW, CCW) durint time 't',
   * and puts in vector 'offset' the corresponding offset
   */
  PhysicsRobot fakeMove(float t, bool rotate, int s, int ang, Vector offset) const;

  /** Moves in the direction of 'offset' vector with a potency
   * proportional to its norm (100 -> 100%)
   */
  void go(Vector offset);

  /**
   * Rotate in place the angle 'ang' [-180,180] 
   */
  void rotate(int ang);

  /** 
   * Moves in the direction of vector 'offset' with a potency
   * proportional to its norm (100 -> 100%) rotating in sense 's' (CW, CCW)
   */
  void move(int s, Vector offset);

  /**
   *  Stops 
   */
  void stop();

  /** 
   * Updates its internal state according to the feedback sent by the real robots'
   * enconders, by radio
   */
  void update();



  /* Getters/Setters */

  int getAngle();
};

#endif //__ROBOPET_PHYSICS_ROBOT_H__

