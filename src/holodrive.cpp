#include "holodrive.h"

vex::holodrive::holodrive(vex::motor *_frontLeft, vex::motor *_frontRight, vex::motor *_backLeft, vex::motor *_backRight) {
    this->frontLeft = _frontLeft;
    this->frontRight = _frontRight;
    this->backLeft = _backLeft;
    this->backRight = _backRight;
}

void vex::holodrive::setStopping(vex::brakeType mode) {
    (*this->frontLeft).setStopping(mode);
    (*this->frontRight).setStopping(mode);
    (*this->backLeft).setStopping(mode);
    (*this->backRight).setStopping(mode);
}

void vex::holodrive::setVelocity(double velocity, vex::velocityUnits units) {
    (*this->frontLeft).setVelocity(velocity, units);
    (*this->frontRight).setVelocity(velocity, units);
    (*this->backLeft).setVelocity(velocity, units);
    (*this->backRight).setVelocity(velocity, units);
}

void vex::holodrive::setVelocity(double velocity, vex::percentUnits units) {
    (*this->frontLeft).setVelocity(velocity, units);
    (*this->frontRight).setVelocity(velocity, units);
    (*this->backLeft).setVelocity(velocity, units);
    (*this->backRight).setVelocity(velocity, units);
}

void vex::holodrive::drive(int x, int y, int w, double velocity, velocityUnits units) {
    (*this->frontLeft).spin(vex::directionType::fwd, (y + x + w) * velocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, (-y + x + w) * velocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, (y - x + w) * velocity, units);
    (*this->backRight).spin(vex::directionType::fwd, (-y - x + w) * velocity, units);
}

void vex::holodrive::drive(int x, int y, int w, double velocity, percentUnits units) {
    (*this->frontLeft).spin(vex::directionType::fwd, (y + x + w) * velocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, (-y + x + w) * velocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, (y - x + w) * velocity, units);
    (*this->backRight).spin(vex::directionType::fwd, (-y - x + w) * velocity, units);
}

void vex::holodrive::driveFor(int x, int y, int w, double velocity, velocityUnits units) {
    (*this->frontLeft).spin(vex::directionType::fwd, (y + x + w) * velocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, (-y + x + w) * velocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, (y - x + w) * velocity, units);
    (*this->backRight).spin(vex::directionType::fwd, (-y - x + w) * velocity, units);
}

void vex::holodrive::driveFor(int x, int y, int w, double velocity, percentUnits units) {
    (*this->frontLeft).spin(vex::directionType::fwd, (y + x + w) * velocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, (-y + x + w) * velocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, (y - x + w) * velocity, units);
    (*this->backRight).spin(vex::directionType::fwd, (-y - x + w) * velocity, units);
}

void vex::holodrive::stop() {
    (*this->frontLeft).stop();
    (*this->frontRight).stop();
    (*this->backLeft).stop();
    (*this->backRight).stop();
}

void vex::holodrive::stop(vex::brakeType mode) {
    (*this->frontLeft).stop(mode);
    (*this->frontRight).stop(mode);
    (*this->backLeft).stop(mode);
    (*this->backRight).stop(mode);
}