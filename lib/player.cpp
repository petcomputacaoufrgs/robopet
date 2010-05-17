#include "player.h"

void Player::setCurrentAngle( double newCurrentAngle )
{ _current_angle = newCurrentAngle; }

void Player::setFutureAngle( double newFutureAngle )
{ _future_angle = newFutureAngle; }

void Player::setDeltaAngle( double newDeltaAngle )
{ _delta_angle = newDeltaAngle; }

void Player::setRole( Role newRole ) { _role = newRole; }

void Player::setDisplacementWithBall( double newDisplacementWithBall )
{ _displacement_with_ball = newDisplacementWithBall; }

void Player::setDriblerIntensity(int intensity)
{ _dribler = intensity; }
void Player::setKickerIntensity(int intensity)
{ _kicker = intensity; }

void Player::setId(int id)
{ _id = id; }

double Player::calcDeltaAngle()
{
  double desl = getFutureAngle() - getCurrentAngle();

  if(fabs(desl) > 180)
	  desl = (360 - fabs(desl)) * ((-desl > 0) ? (1) : (-1));

  setDeltaAngle(desl);

  return getDeltaAngle();
}


Player& Player::operator=(const Player& other)
{
    ((MovingObject*)this)->operator= ( *(dynamic_cast<const MovingObject*>(&other)) );

    setCurrentAngle( other.getCurrentAngle() );
    setFutureAngle( other.getFutureAngle() );
    setDeltaAngle( other.getDeltaAngle() );
    setRole( other.getRole() );

    setDisplacementWithBall( other.getDisplacementWithBall() );

    return *this;
}

