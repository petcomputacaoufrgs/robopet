#ifndef __ROBOPET_PHYSICS_ROBOT_H__
#define __ROBOPET_PHYSICS_ROBOT_H__

#include "vector.h"

/* Physic state of a robot */
class PhysicsRobot {

private:

	int _angle;

public:

	/* rotation sense */
	enum {
		CW = 1,
		CCW = -1
	};

	PhysicsRobot(){}
	PhysicsRobot(int angle);

  /* returns the new physical state after moving in the directon of angle 'ang' [0,360),
   * possibly rotating (rotate) in sense 's' (CW, CCW) durint time 't',
   * and puts in vector 'offset' the corresponding offset
   */
  PhysicsRobot fakeMove(float t, bool rotate, int s, int ang, Vector offset) const;

  /* moves in the direction of 'offset' vector with a potency
   * proportional to its norm (100 -> 100%)
   */
  void go(Vector offset);

  /* rotate in place the angle 'ang' [-180,180] */
  void rotate(int ang);

  /* moves in the direction of vector 'offset' with a potency
   * proportional to its norm (100 -> 100%) rotating in sense 's' (CW, CCW)
   */
  void move(int s, Vector offset);

  /* stops */
  void stop();

  /* updates its internal state according to the feedback sent by the real robots'
   * enconders, by radio
   */
  void update();



  /* Getters/Setters */

  int getAngle();
};

#endif //__ROBOPET_PHYSICS_ROBOT_H__

