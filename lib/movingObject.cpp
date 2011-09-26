#include "movingObject.h"

MovingObject::MovingObject(const MovingObject& other)
{
    *this = other;
}

void MovingObject::setCurrentPosition(Point newCurrentPosition)
{
	_current_position.setX(newCurrentPosition.getX());
	_current_position.setY(newCurrentPosition.getY());
}

void MovingObject::setCurrentPosition(double x, double y)
{
	_current_position.setX(x);
	_current_position.setY(y);
}

void MovingObject::setCurrentPositionX(double x)
{
	_current_position.setX(x);
}

void MovingObject::setCurrentPositionY(double y)
{
	_current_position.setY(y);
}

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

/*----------------------------------------------------
 */
 void MovingObject::setPathplanFuturePosition(Point newFuturePosition)
{ _pathplan_future_position = newFuturePosition; }

 void MovingObject::setPathplanFuturePosition(double x, double y)
{ _pathplan_future_position = Point(x, y); }

void MovingObject::setPathplanFuturePositionX(double x)
{ _pathplan_future_position = Point(x, getPathplanFuturePosition().getY()); }

void MovingObject::setPathplanFuturePositionY(double y)
{ _pathplan_future_position = Point(getPathplanFuturePosition().getX(), y); }

/*----------------------------------------------------
 */
 
void MovingObject::setDisplacement(double displacement)
{ _displacement = displacement; }

Vector MovingObject::calcDisplacementVector()
{ return Vector(getCurrentPosition(), getFuturePosition()); }

void MovingObject::calculateDisplacement()
{ _displacement = calcDisplacementVector().getNorm(); }

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
