/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
#include "holodrive.h"

using namespace vex;

#include "robot_config.h"

/* Button code */

// collect data for on screen button and include off and on color feedback for button
// prc - instead of radio approach with one button on or off at a time, each button has
//          a state.  ie shootPreload may be low yellow and high yellow when on.
typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *offLabel;
    const char *onLabel;
} button;

#define AUTONOMOUS_ALLY pow(2, 0)
#define AUTONOMOUS_DISABLE pow(2, 1)
#define AUTONOMOUS_FAR pow(2, 2)
#define AUTONOMOUS_SKILL pow(2, 3)
#define AUTONOMOUS_NO_PARK pow(2, 4)

#define ALLY_RED 0
#define ALLY_BLUE 1

int autonomousSelection = 0;

int checkAutonomousType(int type) { // Check if button is pressed
    return (autonomousSelection & type) > 0;
}

// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you
// wish as long as it fits.
button buttons[] = {
//  {    X,   Y,  W,  H,  state, offColor, onColor,  offLabel, onLabel }
    {   30,  30, 60, 60,  false, 0xEE0000, 0x0000EE, "Red",    "Blue" },
    {  150,  30, 60, 60,  false, 0x00FF66, 0xFFBB00, "Front",  "Back" },
    {  270,  30, 60, 60,  false, 0x40FF66, 0xFFBB00, "Main",   "Alt" },
    {  390,  30, 60, 60,  false, 0x909090, 0x00FF66, "Comp.",  "Skills" },
    {   30, 150, 60, 60,  false, 0x909090, 0x00FF66, "5-",     "8-" },
    {  150, 150, 60, 60,  false, 0x909090, 0x00FF66, "6-",     "7-" },
    {  270, 150, 60, 60,  false, 0x909090, 0x00FF66, "7-",     "5-" },
    {  390, 150, 60, 60,  false, 0x909090, 0x00FF66, "8-",     "6-" }
};

// forward ref
void displayButtonControls(int index, bool pressed);

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0; index < nButtons; index++) {
        button *pButton = &buttons[ index ];
        if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
            continue;

        if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
            continue;

        return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0; index < nButtons; index++) {
        buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton(xpos, ypos)) >= 0 ) {
        displayButtonControls(index, true);
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton(xpos, ypos)) >= 0 ) {
        // clear all buttons to false, ie. unselected
        //      initButtons();

        // now set this one as true
        if( buttons[index].state == true) {
            buttons[index].state = false;
        }
        else    {
            buttons[index].state = true;
        }

        // set bit of auton selection
        unsigned long newbit = !!buttons[index].state;
        autonomousSelection ^= (-newbit ^ autonomousSelection) & (1UL << index);

        displayButtonControls(index, false);
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor(vex::color(0xe0e0e0));
    Brain.Screen.printAt(10, 20, "%d", autonomousSelection);

    for (int i = 0; i < sizeof(buttons) / sizeof(button); i ++) {

        if (buttons[i].state)
            c = buttons[i].onColor;
        else
            c = buttons[i].offColor;

        Brain.Screen.setFillColor(c);

        // button fill
        if (i == index && pressed == true) {
            Brain.Screen.drawRectangle(buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c);
        }
        else
            Brain.Screen.drawRectangle(buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height);

        // outline
        Brain.Screen.drawRectangle(buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent);
        
        const char *label;
        
        if (buttons[i].state && buttons[i].onLabel != NULL)
            label = buttons[i].onLabel;
        else
            label = buttons[i].offLabel;
        
        // draw label
        if (label != NULL)
            Brain.Screen.printAt(buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, label);
    }
}

/*
 * Autonomous helper functions
 */

/*
void turnRightMotor(int rotations, int speed) {
    RightMotor.startRotateTo(rotations, rotationUnits::deg, speed, velocityUnits::pct);
    RightMotor2.startRotateTo(rotations, rotationUnits::deg, speed, velocityUnits::pct);
}

void turnLeftMotor(int rotations, int speed) {
    LeftMotor.startRotateTo(rotations, rotationUnits::deg, speed, velocityUnits::pct);
    LeftMotor2.startRotateTo(rotations, rotationUnits::deg, speed, velocityUnits::pct);
}

void setRightMotorSpeed(int speed) {
    if (speed) {
        RightMotor.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
        RightMotor2.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    } else {
        RightMotor.stop();
        RightMotor2.stop();
    }
}

void setLeftMotorSpeed(int speed) {
    if (speed) {
        LeftMotor.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
        LeftMotor2.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
    } else {
        LeftMotor.stop();
        LeftMotor2.stop();
    }
}

int sgn(int x) {
    if (x >= 0) return 1;
    else return -1;
}

// Converts distance in inches
int converter(int distancecalc) {
    return distancecalc / (4 * 3.141592653) * 360;
}

// Default drive speed
int driveSpeed = 65;

// Default turn speed
int turnSpeed = 55;

// Drive the robot forward a certain amount of inches. Speed is optional
void driveInches(int inches, int speed) {
    LeftMotor.startRotateFor(converter(inches), rotationUnits::deg, speed, velocityUnits::pct);
    RightMotor.startRotateFor(converter(inches), rotationUnits::deg, speed, velocityUnits::pct);
    LeftMotor2.startRotateFor(converter(inches), rotationUnits::deg, speed, velocityUnits::pct);
    RightMotor2.rotateFor(converter(inches), rotationUnits::deg, speed, velocityUnits::pct);
}

void driveInches(int inches) {
    driveInches(inches, driveSpeed);
}

// Turn the robot a certain amount of degrees. Speed is optional
void turnDegrees(int dist, int speed) {
    LeftMotor.startRotateFor(dist * 4, rotationUnits::deg, speed, velocityUnits::pct);
    RightMotor.startRotateFor(-dist * 4, rotationUnits::deg, speed, velocityUnits::pct);
    LeftMotor2.startRotateFor(dist * 4, rotationUnits::deg, speed, velocityUnits::pct);
    RightMotor2.rotateFor(-dist * 4, rotationUnits::deg, speed, velocityUnits::pct);
}

void turnDegrees(int dist) {
    turnDegrees(dist, turnSpeed);
}
*/

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void preAuton(void) {
    LiftMotor.setStopping(vex::brakeType::hold);
    GrabMotor.setStopping(vex::brakeType::hold);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
    // no
}

// This is code to display the team number
#define BAR_LENGTH 45
#define BAR_WIDTH 14
#define BAR_GAP 12

vex::color bgColor;
vex::color textColor;

void hbar(int x, int y){
    Brain.Screen.setPenWidth(0);
    Brain.Screen.drawCircle(x, y, BAR_WIDTH/2-1, textColor);
    Brain.Screen.drawCircle(x + BAR_LENGTH, y, BAR_WIDTH/2-1, textColor);
    Brain.Screen.setPenWidth(BAR_WIDTH);
    Brain.Screen.drawLine(x, y, x + BAR_LENGTH, y);
}
void vbar(int x, int y){
    Brain.Screen.setPenWidth(0);
    Brain.Screen.drawCircle(x, y, BAR_WIDTH/2-1, textColor);
    Brain.Screen.drawCircle(x, y + BAR_LENGTH, BAR_WIDTH/2-1, textColor);
    Brain.Screen.setPenWidth(BAR_WIDTH);
    Brain.Screen.drawLine(x, y, x, y + BAR_LENGTH);
}

void H1(int x, int y){
    hbar(x, y); // H1    
}

void H2(int x, int y){
    hbar(x, y + BAR_GAP*2 + BAR_LENGTH); // H2
}

void H3(int x, int y){
    hbar(x, y + BAR_GAP*4 + BAR_LENGTH*2); // H3
}

void V1(int x, int y){
    vbar(x-BAR_GAP, y+BAR_GAP); // V1    
}

void V2(int x, int y){
    vbar(x + BAR_LENGTH + BAR_GAP, y+BAR_GAP); // V2
}

void V3(int x, int y){
    vbar(x-BAR_GAP, y + BAR_GAP*3 + BAR_LENGTH); // V3
}

void V4(int x, int y){
    vbar(x + BAR_LENGTH + BAR_GAP, y + BAR_GAP*3 + BAR_LENGTH); // V4   
}

void one(int x, int y){
    V2(x,y); V4(x,y);
}

void two(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);    
    V2(x,y); V3(x,y);
}

void three(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);
    V2(x,y); V4(x,y);
}

void four(int x, int y){
    H2(x,y);
    V1(x,y); V2(x,y); V4(x,y);
}

void five(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);
    V1(x,y); V4(x,y);
}

void six(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);
    V1(x,y); V3(x,y); V4(x,y);
}

void seven(int x, int y){
    H1(x,y); 
    V2(x,y); V4(x,y);
}

void eight(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);
    V1(x,y); V2(x,y); V3(x,y); V4(x,y);
}

void nine(int x, int y){
    H1(x,y); H2(x,y); H3(x,y);
    V1(x,y); V2(x,y); V4(x,y);
}

void drawNumbers() {
    bgColor = checkAutonomousType(AUTONOMOUS_ALLY) == ALLY_RED ? vex::color::red : vex::color::blue;
    textColor = vex::color::white;
    Brain.Screen.clearScreen(bgColor);
    Brain.Screen.setFillColor(textColor);
    Brain.Screen.setPenColor(textColor);
    
    eight(30, 50);
    seven(120, 50);
    five(210, 50);
    six(300, 50);
    
    // a
    int x = 390;
    int y = 50;
    H1(x, y); H2(x, y);
    V1(x, y); V2(x, y); V3(x, y); V4(x, y);
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

#define CONTROL_DEAD_ZONE 5
#define MAX_MOTOR_SPEED_CHANGE 25
#define TASK_REFRESH_SPEED 20

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int frontLeftSpeed = 0, frontRightSpeed = 0, backLeftSpeed = 0, backRightSpeed = 0;

void adjustMotors(int xMove, int yMove, int wMove) {
    int flMove = yMove + xMove + wMove;
    int frMove = -yMove + xMove + wMove;
    int blMove = yMove - xMove + wMove;
    int brMove = -yMove - xMove + wMove;

    frontLeftSpeed += MAX_MOTOR_SPEED_CHANGE * (frontLeftSpeed < flMove ? 1 : -1);
    frontRightSpeed += MAX_MOTOR_SPEED_CHANGE * (frontRightSpeed < frMove ? 1 : -1);
    backLeftSpeed += MAX_MOTOR_SPEED_CHANGE * (backLeftSpeed < blMove ? 1 : -1);
    backRightSpeed += MAX_MOTOR_SPEED_CHANGE * (backRightSpeed < brMove ? 1 : -1);

    FrontLeftMotor.spin(vex::directionType::fwd, frontLeftSpeed, vex::velocityUnits::pct);
    FrontRightMotor.spin(vex::directionType::fwd, frontRightSpeed, vex::velocityUnits::pct);
    BackLeftMotor.spin(vex::directionType::fwd, backLeftSpeed, vex::velocityUnits::pct);
    BackRightMotor.spin(vex::directionType::fwd, backRightSpeed, vex::velocityUnits::pct);
}

int monitor() {
    Controller1.Screen.clearScreen(); // erase the default screen
    while (true) {
        // Code to monitor sensors or motors goes here

        vex::task::sleep(100);
    }
}

int filterInput(int input) {
    if (abs(input) <= CONTROL_DEAD_ZONE) return 0;
    return input * input * input / 10000;
}

void usercontrol(void) {
    vex::task monitorTask(monitor);
    
    drawNumbers();
    
    while (true) {
        // weeeeeeeeeeeeeeeeeeeeeeeeeeee
        if (!Controller1.ButtonA.pressing())
            adjustMotors(filterInput(Controller1.Axis4.position(vex::percentUnits::pct)), filterInput(Controller1.Axis3.position(vex::percentUnits::pct)), filterInput(Controller1.Axis1.position(vex::percentUnits::pct)));

        if (Controller1.ButtonR1.pressing()) {
            GrabMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
        } else if (Controller1.ButtonR2.pressing()) {
            GrabMotor.spin(vex::directionType::fwd, -50, vex::velocityUnits::pct);
        } else {
            GrabMotor.stop();
        }

        if (Controller1.ButtonL2.pressing() && !BottomLimit.pressing()) {
            LiftMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        } else if (Controller1.ButtonL1.pressing() && !TopLimit.pressing()) {
            LiftMotor.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
        } else if (Controller1.ButtonA.pressing()) {
            Holodrive.drive(0, 1, 0, 100, vex::velocityUnits::pct);
        } else {
            LiftMotor.stop();
        }

        vex::task::sleep(TASK_REFRESH_SPEED);
    }

}

//
// Main will set up the competition functions and callbacks.
//

int main() {
    // Run the pre-autonomous function.
    preAuton();

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Attach button panel events
    Brain.Screen.pressed(userTouchCallbackPressed);
    Brain.Screen.released(userTouchCallbackReleased);

    // Do the buttons
    displayButtonControls(0, false);

    // Prevent main from exiting with an infinite loop.
    while(1) {
        vex::task::sleep(100); // Sleep the task for a short amount of time to prevent wasted resources.
    }
}