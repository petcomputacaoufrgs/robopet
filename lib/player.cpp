#include "player.h"
#include "constants.h"

void Player::setCurrentAngle( double newCurrentAngle )
{ _current_angle = newCurrentAngle; }

void Player::setFutureAngle( double newFutureAngle )
{ //_future_angle = newFutureAngle; 
}

void Player::setDeltaAngle( double newDeltaAngle )
{ _delta_angle = newDeltaAngle; }

void Player::setRole( int newRole ) { _role = newRole; }

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
	//this.setPathplanFuturePosition( _ball.getPosition() );
}

void Player::keepDistanceToBall(double d) {
	
}

void Player::keepDistanceToBall(MovingObject m, double d) {
	double ma,xp,yp;
	if(!isAt(m.getPosition(), d+80))
		setPathplanFuturePosition(m.getPosition());
	else
	{
		if(isAt(m.getPosition(), d))
		{//vai pra tras
			ma = (m.getPosition().getY() - this->getPosition().getY())/(m.getPosition().getX() - this->getPosition().getX());
			if(this->getPosition().getX() <= m.getPosition().getX()) //robo ta na esquerda da bola
			{
				xp=(d/sqrt(1+ma*ma))-m.getPosition().getX();
				yp = ma*(xp-m.getPosition().getX())+m.getPosition().getY();
			}
			else
			{
				xp=(d/sqrt(1+ma*ma))+m.getPosition().getX();
				yp = ma*(xp-m.getPosition().getX())+m.getPosition().getY();
			}
			setPathplanFuturePosition(Point(xp,yp));
		}
		else
			stay();
	}
}

void Player::pointTo( Point p )
{
	RP::Vector playerToPVector(this->getPosition(),p);
	int angle = playerToPVector.myAngleDegrees();
	
	if(angle>180)
		angle = angle - 360;

	this->setFutureAngle( angle );
}

bool Player::isPointingTo( Point p)
{	
	//ball_vec is the vector from the bot center to the ball center
	RP::Vector desiredDirection(this->getPosition(), p);
	desiredDirection.normalizeMe();

	//bot_vec indicates where the bot is pointing
	RP::Vector actualDirection( cos(this->getCurrentAngle())*ROBOT_RADIUS_MM,
								sin(this->getCurrentAngle())*ROBOT_RADIUS_MM);
	actualDirection.normalizeMe();

	float dotProd = desiredDirection.dotProduct(actualDirection);
	//desiredDirection (dot_product) actualDirection = |desiredDirection| * |actualDirection| * cos(theta)
	//|desiredDirection| == |actualDirection| == 1, because both are normalized
	//if theta ~ 0, the bot points to the ball
	
	if(dotProd >= 0 && .95 <= dotProd)
	{
		return true;
	}
	
	return false;
}
void Player::follow(MovingObject m)
{
	setPathplanFuturePosition(m.getPosition());
	double angle = Vector(getPosition(),m.getPosition()).angle(Vector(1,0));
	setFutureAngle( angle );
}

void Player::goToPoint(Point p)
{
	setPathplanFuturePosition(p);
	double angle = Vector(getPosition(),p).angle(Vector(1,0));
	setFutureAngle( angle );
}
void Player::stay()
{
	setPathplanFuturePosition(getCurrentPosition());
	setFutureAngle(getCurrentAngle());
}

bool Player::isAt(Point p, int distance_threshold)
{
	return this->getPosition().getDistance(p) <= distance_threshold;
}
