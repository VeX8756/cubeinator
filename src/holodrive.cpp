#include "holodrive.h"
#include <cmath>

vex::holodrive::holodrive(vex::motor *_frontLeft, vex::motor *_frontRight, vex::motor *_backLeft, vex::motor *_backRight, double wheelDiameter, vex::distanceUnits wheelDiameterUnits) {
    this->frontLeft = _frontLeft;
    this->frontRight = _frontRight;
    this->backLeft = _backLeft;
    this->backRight = _backRight;
    if (wheelDiameterUnits == vex::distanceUnits::mm) wheelDiameter /= 25.4;
    if (wheelDiameterUnits == vex::distanceUnits::cm) wheelDiameter /= 2.54;
    this->wheelCircumference = wheelDiameter * M_PI;
}

void vex::holodrive::setStopping(vex::brakeType mode) {
    (*this->frontLeft).setStopping(mode);
    (*this->frontRight).setStopping(mode);
    (*this->backLeft).setStopping(mode);
    (*this->backRight).setStopping(mode);
}

void vex::holodrive::drive(double xVelocity, double yVelocity, vex::velocityUnits units) {
    (*this->frontLeft).spin(vex::directionType::fwd, yVelocity + xVelocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, -yVelocity + xVelocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, yVelocity - xVelocity, units);
    (*this->backRight).spin(vex::directionType::fwd, -yVelocity - xVelocity, units);
}

void vex::holodrive::drive(double xVelocity, double yVelocity, vex::percentUnits units) {
    this->drive(xVelocity, yVelocity, vex::velocityUnits::pct);
}

double vex::holodrive::calcSpeed(double start, double rot, double end) {
    double totalDist = std::abs(end - start);
    double curDistStart = std::abs(rot - start);
    double curDistEnd = std::abs(end - rot);
    double minSpeed = 0.5;
    if (curDistStart < 5) return (1 - minSpeed) * (curDistStart / 5) + minSpeed;
    if (curDistEnd < 5) return (1 - minSpeed) * (curDistEnd / 5) + minSpeed;
    return 1;
}

//#define canGo(r, f) (dir == vex::directionType::fwd && (f) - (r) > STOP_DISTANCE) || (dir == vex::directionType::rev && (r) - (f) > STOP_DISTANCE)
#define canGo(r, f) std::abs((f) - (r)) > std::abs((xVelocity + yVelocity) / 200) * 10

// almost PID, but not quite
void vex::holodrive::driveFor(double distance, distanceUnits dUnits, double xVelocity, double yVelocity, vex::velocityUnits units, bool waitForCompletion) {
    if (dUnits == vex::distanceUnits::mm) distance /= 25.4;
    if (dUnits == vex::distanceUnits::cm) distance /= 2.54;

    vex::directionType dir = vex::directionType::fwd;

    if (distance < 0) {
        dir = vex::directionType::rev;
        distance = -distance;
        xVelocity = -xVelocity;
        yVelocity = -yVelocity;
    }

    double root = 0;

    if (xVelocity > yVelocity && xVelocity > 0) root = std::abs(std::abs(xVelocity) - std::abs(yVelocity)) / std::abs(xVelocity);
    if (xVelocity < yVelocity && yVelocity > 0) root = std::abs(std::abs(yVelocity) - std::abs(xVelocity)) / std::abs(yVelocity);
    if (xVelocity > yVelocity && yVelocity < 0) root = std::abs(std::abs(xVelocity) - std::abs(yVelocity)) / std::abs(yVelocity);
    if (xVelocity < yVelocity && xVelocity < 0) root = std::abs(std::abs(yVelocity) - std::abs(xVelocity)) / std::abs(xVelocity);

    float degrees = (distance / (this->wheelCircumference / 360)) / (((sqrt(2) - 1) * root) + 1);

    float flDegrees = (yVelocity + xVelocity) < 0 ? -degrees : degrees;
    float frDegrees = (-yVelocity + xVelocity) < 0 ? -degrees : degrees;
    float blDegrees = (yVelocity - xVelocity) < 0 ? -degrees : degrees;
    float brDegrees = (-yVelocity - xVelocity) < 0 ? -degrees : degrees;

    this->stop();

    const double flFinal = (*this->frontLeft).rotation(vex::rotationUnits::deg) + flDegrees;
    const double frFinal = (*this->frontRight).rotation(vex::rotationUnits::deg) + frDegrees;
    const double blFinal = (*this->backLeft).rotation(vex::rotationUnits::deg) + blDegrees;
    const double brFinal = (*this->backRight).rotation(vex::rotationUnits::deg) + brDegrees;

    int stoppedMotors = 0;

    while (stoppedMotors < 4) {
        double flRot = (*this->frontLeft).rotation(vex::rotationUnits::deg);
        double frRot = (*this->frontRight).rotation(vex::rotationUnits::deg);
        double blRot = (*this->backLeft).rotation(vex::rotationUnits::deg);
        double brRot = (*this->backRight).rotation(vex::rotationUnits::deg);

        if (canGo(flRot, flFinal))
            (*this->frontLeft).spin(vex::directionType::fwd, (yVelocity + xVelocity) * this->calcSpeed(flFinal - flDegrees, flRot, flFinal), units);
        else {
            (*this->frontLeft).stop();
            stoppedMotors ++;
        }

        if (canGo(frRot, frFinal))
            (*this->frontRight).spin(vex::directionType::fwd, (-yVelocity + xVelocity) * this->calcSpeed(frFinal - frDegrees, frRot, frFinal), units);
        else {
            (*this->frontRight).stop();
            stoppedMotors ++;
        }

        if (canGo(blRot, blFinal))
            (*this->backLeft).spin(vex::directionType::fwd, (yVelocity - xVelocity) * this->calcSpeed(blFinal - blDegrees, blRot, blFinal), units);
        else {
            (*this->backLeft).stop();
            stoppedMotors ++;
        }

        if (canGo(brRot, brFinal))
            (*this->backRight).spin(vex::directionType::fwd, (-yVelocity - xVelocity) * this->calcSpeed(brFinal - brDegrees, brRot, brFinal), units);
        else {
            (*this->backRight).stop();
            stoppedMotors ++;
        }
    }

    this->stop();
}

void vex::holodrive::driveFor(double distance, distanceUnits dUnits, double xVelocity, double yVelocity, vex::percentUnits units, bool waitForCompletion) {
    this->driveFor(distance, dUnits, xVelocity, yVelocity, vex::velocityUnits::pct, waitForCompletion);
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

void vex::holodrive::turn(vex::turnType dir, double velocity, vex::velocityUnits units) {
    if (dir == vex::turnType::left) velocity = -velocity;
    (*this->frontLeft).spin(vex::directionType::fwd, velocity, units);
    (*this->frontRight).spin(vex::directionType::fwd, velocity, units);
    (*this->backLeft).spin(vex::directionType::fwd, velocity, units);
    (*this->backRight).spin(vex::directionType::fwd, velocity, units);
}

void vex::holodrive::turn(vex::turnType dir, double velocity, vex::percentUnits units) {
    this->turn(dir, velocity, vex::velocityUnits::pct);
}

void vex::holodrive::turnFor(double degrees,double velocity, vex::velocityUnits units) {
    (*this->frontLeft).startRotateTo(degrees, vex::rotationUnits::deg, velocity, units);
    (*this->frontRight).startRotateTo(degrees, vex::rotationUnits::deg, velocity, units);
    (*this->backLeft).startRotateTo(degrees, vex::rotationUnits::deg, velocity, units);
    (*this->backRight).rotateTo(degrees, vex::rotationUnits::deg, velocity, units);
}

void vex::holodrive::turnFor(double degrees, double velocity, vex::percentUnits units) {
    this->turnFor(degrees, velocity, vex::velocityUnits::pct);
}