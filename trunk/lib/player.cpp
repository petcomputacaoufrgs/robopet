#include "player.h"
#include "constants.h"

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

void Player::kick() {
	this->setKickerIntensity(999);
	//this.setFuturePosition( _ball.getPosition() );
}

void Player::pointTo( Point p )
{
	RP::Vector playerToPVector(this->getPosition(),p);
	int angle = playerToPVector.angleDegrees(Vector(1,0));
	
	if(playerToPVector.getY() > 0)
		angle = 360 - angle;
	
	this->setFutureAngle( angle );
}

bool Player::isPointingTo( Point p)
{
	int treshold = 0.1; //percentage of error
	
	//ball_vec is the vector from the bot center to the ball center
	RP::Vector desiredDirection(this->getPosition(), p);
	desiredDirection.normalizeMe();

	//bot_vec indicates where the bot is pointing
	RP::Vector actualDirection( cos(this->getCurrentAngle())*ROBOT_RADIUS_MM,
								sin(this->getCurrentAngle())*ROBOT_RADIUS_MM);
	actualDirection.normalizeMe();
	
	//desiredDirection (dot_product) actualDirection = |desiredDirection| * |actualDirection| * cos(theta)
	//|desiredDirection| == |actualDirection| == 1, because both are normalized
	//if theta ~ 0, the bot points to the ball
	if(1-treshold <= desiredDirection.dotProduct(actualDirection))
		return true;
	else
		return false;
}
