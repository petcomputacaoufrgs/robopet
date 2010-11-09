#include "physicsRobot.h"

PhysicsRobot::PhysicsRobot(int angle) {

	_angle = angle;
}

PhysicsRobot PhysicsRobot::fakeMove(float t, bool rotate,int s, int ang, Vector &offset) const {

	offset.setXY(1,0);
	offset.rotate(_angle + ang);
	offset = offset * t;

	return PhysicsRobot(rotate ? _angle + s : _angle);
}

void PhysicsRobot::go(Vector offset) {

}

void PhysicsRobot::rotate(int ang) {

}

void PhysicsRobot::move(int s, Vector offset) {

}

void PhysicsRobot::stop() {

}

void PhysicsRobot::update() {

}

int PhysicsRobot::getAngle() {

	return _angle;
}
