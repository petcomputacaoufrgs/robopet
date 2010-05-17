#ifndef _ROBOPET_BALL_H_
#define _ROBOPET_BALL_H

#include "point.h"
#include "movingObject.h"

class Ball : public MovingObject
{

    public:

        Ball(double startX = 0,double startY = 0){ _current_position = Point(startX,startY); }
        ~Ball() {}

	private:

};

#endif // _ROBOPET_BALL_H_
