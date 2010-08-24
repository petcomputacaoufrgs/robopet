#ifndef __ROBOPET_MOVING_OBJECT_H__
#define __ROBOPET_MOVING_OBJECT_H__

#include "point.h"
#include "vector.h"
#include "robopet.h"

using RP::Point;
using RP::Vector;
using RP::MovingObject;

class MovingObject
{
  public:
    MovingObject() : _current_position(0, 0), _past_position(0, 0), _future_position(0, 0) {}
    MovingObject(const MovingObject& other);
    ~MovingObject() {}

    //----- Getters -----
    inline const Point& getCurrentPosition() const { return _current_position; }
    inline const Point& getPastPosition() const { return _past_position; }
    inline const Point& getFuturePosition() const { return _future_position; }

	inline double getDisplacement() const { return _displacement; }

    //----- Setters -----
    void setCurrentPosition(Point newCurrentPosition);
    void setCurrentPosition(double x, double y);
    void setCurrentPositionX(double x);
    void setCurrentPositionY(double y);

    void setPastPosition(Point newPastPosition);
    void setPastPosition(double x, double y);
    void setPastPositionX(double x);
    void setPastPositionY(double y);

    void setFuturePosition(Point newFuturePosition);
    void setFuturePosition(double x, double y);
    void setFuturePositionX(double x);
    void setFuturePositionY(double y);

	void setDisplacement(double displacement);
    //----- Others -----
    Vector calcDisplacementVector();
    void calculateDisplacement();
    
    double getDistance(const MovingObject& other);


    //----- Operators -----
    MovingObject& operator=(const MovingObject& other);

  protected:
    Point _current_position;
    Point _past_position;
    Point _future_position;

    double _displacement;

};

#endif //__ROBOPET_MOVING_OBJECT_H__

