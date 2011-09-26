#ifndef __ROBOPET_MOVING_OBJECT_H__
#define __ROBOPET_MOVING_OBJECT_H__

#include "point.h"
#include "vector.h"
#include "robopet.h"

using RP::Point;
using RP::Vector;
using RP::MovingObject;

/**
 * Basic class for any moving objects.
 * \ingroup RoboPETLib
 */
class MovingObject
{
  public:
    MovingObject(double stX = 0, double stY = 0) : _current_position(stX, stY), _past_position(-1, -1), _future_position(-1, -1), _pathplan_future_position (-1,-1) {}
	MovingObject(const MovingObject& other);
    ~MovingObject() {}

    //----- Getters -----
    inline const Point& getCurrentPosition() const { return _current_position; }
    inline const Point& getPastPosition() const { return _past_position; }
    inline const Point& getFuturePosition() const { return _future_position; }

    inline const Point& getPathplanFuturePosition() const { return _pathplan_future_position; }

    inline double getDisplacement() const { return _displacement; }

    inline const Point& getPosition() const { return getCurrentPosition(); }

    //----- Setters -----
    void setCurrentPosition(Point newCurrentPosition);
    void setCurrentPosition(double x, double y);
    void setCurrentPositionX(double x);
    void setCurrentPositionY(double y);

    inline void setX(double x) { setCurrentPositionX(x); }
    inline void setY(double y) { setCurrentPositionY(y); }

    inline double getX() { return getCurrentPosition().getX(); }
    inline double getY() { return getCurrentPosition().getY(); }

    void setPastPosition(Point newPastPosition);
    void setPastPosition(double x, double y);
    void setPastPositionX(double x);
    void setPastPositionY(double y);

    void setFuturePosition(Point newFuturePosition);
    void setFuturePosition(double x, double y);
    void setFuturePositionX(double x);
    void setFuturePositionY(double y);

    void setPathplanFuturePosition(Point newFuturePosition);
    void setPathplanFuturePosition(double x, double y);
    void setPathplanFuturePositionX(double x);
    void setPathplanFuturePositionY(double y);

    void setDisplacement(double displacement);
   
    //----- Others -----
    
    /**
     * @return The displacement vector
    */
    Vector calcDisplacementVector();
    
    /**
     * set the displacement to be the norm of the displacement vector
    */
    void calculateDisplacement();
    
    double getDistance(const MovingObject& other);


    //----- Operators -----
    MovingObject& operator=(const MovingObject& other);

  protected:
    Point _current_position;
    Point _past_position;
    Point _future_position;
    Point _pathplan_future_position;

    double _displacement;

};

#endif //__ROBOPET_MOVING_OBJECT_H__

