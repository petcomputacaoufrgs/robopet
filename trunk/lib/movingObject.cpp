#include "movingObject.h"

MovingObject::MovingObject(const MovingObject& other)
{
    *this = other;
}

void MovingObject::setCurrentPosition(Point newCurrentPosition)
{ _current_position = newCurrentPosition; }

void MovingObject::setCurrentPosition(double x, double y)
{ _current_position = Point(x, y); }

void MovingObject::setCurrentPositionX(double x)
{ _current_position = Point(x, getCurrentPosition().getY()); }

void MovingObject::setCurrentPositionY(double y)
{ _current_position = Point(getCurrentPosition().getX(), y); }



void MovingObject::setPastPosition(Point newPastPosition)
{ _past_position = newPastPosition; }

void MovingObject::setPastPosition(double x, double y)
{ _past_position = Point(x, y); }

void MovingObject::setPastPositionX(double x)
{ _past_position = Point(x, getPastPosition().getY()); }

void MovingObject::setPastPositionY(double y)
{ _past_position = Point(getPastPosition().getX(), y); }


void MovingObject::setFuturePosition(Point newFuturePosition)
{ _future_position = newFuturePosition; }

void MovingObject::setFuturePosition(double x, double y)
{ _future_position = Point(x, y); }

void MovingObject::setFuturePositionX(double x)
{ _future_position = Point(x, getFuturePosition().getY()); }

void MovingObject::setFuturePositionY(double y)
{ _future_position = Point(getFuturePosition().getX(), y); }


void MovingObject::setDisplacement(double displacement)
{ _displacement = displacement; }



Vector MovingObject::calcDisplacementVector()
{ return Vector(getCurrentPosition(), getFuturePosition()); }

//void MovingObject::calculateDisplacement()
//{ _displacement = calcDisplacementVector().getNorm(); }

double MovingObject::getDistance(const MovingObject& other) {
	
	return _current_position.getDistance(other.getCurrentPosition());
}



MovingObject& MovingObject::operator=(const MovingObject& other)
{
    setCurrentPosition( other.getCurrentPosition() );
    setPastPosition( other.getPastPosition() );
    setFuturePosition( other.getFuturePosition() );

    //calculate the current displacement before copying
    //calculateDisplacement();
    setDisplacement( other.getDisplacement() );

    return *this;
}
