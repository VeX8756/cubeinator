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

        public:
            holodrive(motor *_frontLeft, motor *_frontRight, motor *_backLeft, motor *_backRight);
            
            void setStopping(brakeType mode);

            void setVelocity(double velocity, velocityUnits units);
            void setVelocity(double velocity, percentUnits units);

            void drive(int x, int y, int w, double velocity, velocityUnits units);
            void drive(int x, int y, int w, double velocity, percentUnits units);

            void stop();
            void stop(brakeType mode);
    };
};

#endif