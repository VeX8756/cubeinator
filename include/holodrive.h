#include "vex.h"

#ifndef VEX_HOLOTRAIN_CLASS_H
#define VEX_HOLOTRAIN_CLASS_H

namespace vex {
    class holodrive {
        private:
            motor *frontLeft;
            motor *frontRight;
            motor *backLeft;
            motor *backRight;

            int frontLeftMove;
            int frontRightMove;
            int backLeftMove;
            int backRightMove;

            double wheelCircumference;

            double calcSpeed(double start, double rot, double end);
        public:
            holodrive(motor *_frontLeft, motor *_frontRight, motor *_backLeft, motor *_backRight, double wheelDiameter = 4.125, distanceUnits wheelDiameterUnits = distanceUnits::in);
            
            void setStopping(brakeType mode);
            
            void drive(double xVelocity, double yVelocity, velocityUnits units);
            void drive(double xVelocity, double yVelocity, percentUnits units);

            void driveFor(double distance, distanceUnits dUnits, double xVelocity, double yVelocity, velocityUnits units, bool waitForCompletion = true);
            void driveFor(double distance, distanceUnits dUnits, double xVelocity, double yVelocity, percentUnits units, bool waitForCompletion = true);

            void turn(turnType dir, double velocity, velocityUnits units);
            void turn(turnType dir, double velocity, percentUnits units);

            void turnFor(double degrees, double velocity, velocityUnits units);
            void turnFor(double degrees, double velocity, percentUnits units);

            void stop();
            void stop(brakeType mode);
    };
};

#endif