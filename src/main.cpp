/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"
#include "holodrive.h"
#include "threedee.h"

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

bool checkAutonomousType(int type) { // Check if button is pressed
    return (autonomousSelection & type) > 0;
}

bool canSelectAuton = true;

// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you
// wish as long as it fits.
button buttons[] = {
//  {    X,   Y,  W,  H,  state, offColor, onColor,  offLabel, onLabel }
    {   30,  30, 60, 60,  false, 0xee0000, 0x0000ee, "Red",    "Blue" },
    {  150,  30, 60, 60,  false, 0x00ff66, 0xffbb00, "Front",  "Back" },
    {  270,  30, 60, 60,  false, 0x40ff66, 0xffbb00, "Main",   "Alt" },
    {  390,  30, 60, 60,  false, 0x909090, 0x00ff66, "Comp.",  "Skills" },
    {   30, 150, 60, 60,  false, 0x909090, 0x00ff66, "5-",     "8-" },
    {  150, 150, 60, 60,  false, 0x909090, 0x00ff66, "6-",     "7-" },
    {  270, 150, 60, 60,  false, 0x909090, 0x00ff66, "7-",     "5-" },
    {  390, 150, 60, 60,  false, 0x909090, 0x00ff66, "8-",     "6-" }
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
    if (!canSelectAuton) return;

    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if ((index = findButton(xpos, ypos)) >= 0) {
        displayButtonControls(index, true);
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    if (!canSelectAuton) return;

    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if ((index = findButton(xpos, ypos)) >= 0) {
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
    /*FrontLeftMotor.setStopping(vex::brakeType::hold);
    FrontRightMotor.setStopping(vex::brakeType::hold);
    BackLeftMotor.setStopping(vex::brakeType::hold);
    BackRightMotor.setStopping(vex::brakeType::hold);*/
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
    canSelectAuton = false;

    // drive forward 7 inches
    Holodrive.driveFor(7, vex::distanceUnits::in, 0, 50, vex::velocityUnits::pct);

    // drive back 4 inches
    Holodrive.driveFor(4, vex::distanceUnits::in, 0, -50, vex::velocityUnits::pct);

    // need to rewrite for distance
    /*
    Drive(true, 1000);//drive forward until you reach the first cube
    
    Claw.spinFor(forward, 90, degrees, Vel, velocityUnits::pct);//close claw 90 degrees so that way it is holding the cube

    ArmMotors.rotateTo(90, degrees, Vel, velocityUnits::pct);//lift claw up to the height of 4 cubes plus the one that the claw is holding

    Drive(true, 357); //drive to where the cube that we are holding is directly above the 4 cube stack

    Claw.spinFor(reverse, 850, msec, Vel, velocityUnits::pct);//drop the cube that is being held down onto the stack

    ArmMotors.rotateTo(-90, degrees, Vel, velocityUnits::pct);//drop claw down to the level of the 1st cube on the bottom of the stack

    Claw.spinFor(forward, 90, degrees, Vel, velocityUnits::pct);//close claw

    ArmMotors.rotateTo(45, degrees, Vel, velocityUnits::pct);//lift up the claw by half a cube distance

    Drivetrain.turnFor(90, degrees, Vel, velocityUnits::pct);//turn robot 90 degrees left

    Strafe(false, 1000);//drive left until the robot reaches the wall

    Drive(true, 714);//drive forward until the robot is right in front of the goal

    ArmMotors.rotateTo(-45, degrees, Vel, velocityUnits::pct);//lower claw to where the cubes are down on the ground
   
    Claw.spinFor(forward, 90, degrees, Vel, velocityUnits::pct);//release the claw
    
    Drive(false, 714);  //back up
    */
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
    hbar(x, y + BAR_GAP * 2 + BAR_LENGTH); // H2
}

void H3(int x, int y){
    hbar(x, y + BAR_GAP * 4 + BAR_LENGTH * 2); // H3
}

void V1(int x, int y){
    vbar(x - BAR_GAP, y + BAR_GAP); // V1    
}

void V2(int x, int y){
    vbar(x + BAR_LENGTH + BAR_GAP, y + BAR_GAP); // V2
}

void V3(int x, int y){
    vbar(x - BAR_GAP, y + BAR_GAP * 3 + BAR_LENGTH); // V3
}

void V4(int x, int y){
    vbar(x + BAR_LENGTH + BAR_GAP, y + BAR_GAP * 3 + BAR_LENGTH); // V4   
}

void one(int x, int y){
    V2(x, y); V4(x, y);
}

void two(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);    
    V2(x, y); V3(x, y);
}

void three(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);
    V2(x, y); V4(x, y);
}

void four(int x, int y){
    H2(x, y);
    V1(x, y); V2(x, y); V4(x, y);
}

void five(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);
    V1(x, y); V4(x, y);
}

void six(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);
    V1(x, y); V3(x, y); V4(x, y);
}

void seven(int x, int y){
    H1(x, y); 
    V2(x, y); V4(x, y);
}

void eight(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);
    V1(x, y); V2(x, y); V3(x, y); V4(x, y);
}

void nine(int x, int y){
    H1(x, y); H2(x, y); H3(x, y);
    V1(x, y); V2(x, y); V4(x, y);
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

// 3d shit - wrote this pretty much just to show off

int32_t cubeRed[][10] = {
    // back
    { -10,  10, -10, -10, -10, -10, -10, -10,  10, 0xee0000 },
    { -10,  10, -10, -10, -10,  10, -10,  10,  10, 0xee0000 },
    // front
    {  10,  10, -10,  10, -10, -10,  10, -10,  10, 0xee0000 },
    {  10,  10, -10,  10, -10,  10,  10,  10,  10, 0xee0000 },
    // bottom
    {  10, -10, -10, -10, -10, -10, -10,  10, -10, 0xee0000 },
    {  10, -10, -10, -10,  10, -10,  10,  10, -10, 0xee0000 },
    // top
    {  10, -10,  10, -10, -10,  10, -10,  10,  10, 0xee0000 },
    {  10, -10,  10, -10,  10,  10,  10,  10,  10, 0xee0000 },
    // left
    { -10, -10,  10, -10, -10, -10,  10, -10, -10, 0xee0000 },
    { -10, -10,  10,  10, -10, -10,  10, -10,  10, 0xee0000 },
    // right
    { -10,  10,  10, -10,  10, -10,  10,  10, -10, 0xee0000 },
    { -10,  10,  10,  10,  10, -10,  10,  10,  10, 0xee0000 }
};

int32_t cubeBlue[][10] = {
    // back
    { -10,  10, -10, -10, -10, -10, -10, -10,  10, 0x0000ee },
    { -10,  10, -10, -10, -10,  10, -10,  10,  10, 0x0000ee },
    // front
    {  10,  10, -10,  10, -10, -10,  10, -10,  10, 0x0000ee },
    {  10,  10, -10,  10, -10,  10,  10,  10,  10, 0x0000ee },
    // bottom
    {  10, -10, -10, -10, -10, -10, -10,  10, -10, 0x0000ee },
    {  10, -10, -10, -10,  10, -10,  10,  10, -10, 0x0000ee },
    // top
    {  10, -10,  10, -10, -10,  10, -10,  10,  10, 0x0000ee },
    {  10, -10,  10, -10,  10,  10,  10,  10,  10, 0x0000ee },
    // left
    { -10, -10,  10, -10, -10, -10,  10, -10, -10, 0x0000ee },
    { -10, -10,  10,  10, -10, -10,  10, -10,  10, 0x0000ee },
    // right
    { -10,  10,  10, -10,  10, -10,  10,  10, -10, 0x0000ee },
    { -10,  10,  10,  10,  10, -10,  10,  10,  10, 0x0000ee }
};

void draw3d(int xRot, int yRot) {
    ThreeDee.reset();
    ThreeDee.setCam(-50, 0, 0, 0, 0);
    if (checkAutonomousType(AUTONOMOUS_ALLY) == ALLY_RED)
        ThreeDee.drawModel(cubeRed, 12, 0, 0, 4, xRot, yRot);
    else if (checkAutonomousType(AUTONOMOUS_ALLY) == ALLY_BLUE)
        ThreeDee.drawModel(cubeBlue, 12, 0, 0, 4, xRot, yRot);
    ThreeDee.drawText(0, 224, 1, 0xffffff, "CUBEINATOR");
    ThreeDee.draw(Brain.Screen);
    //Brain.Screen.waitForRefresh(); // fucking fix this already
    vex::task::sleep(1000 / 60);
}

int screenUpdate() {
    int xRot = 0;
    int yRot = 0;

    while (true) {
        int rSteps = rand() % 50 + 10;
        switch (rand() % 4) {
            case 0:
                for (int j = 0; j < rSteps; j ++) {
                    xRot ++;
                    draw3d(xRot, yRot);
                }
                break;
            case 1:
                for (int j = 0; j < rSteps; j ++) {
                    xRot --;
                    draw3d(xRot, yRot);
                }
                break;
            case 2:
                for (int j = 0; j < rSteps; j ++) {
                    yRot ++;
                    draw3d(xRot, yRot);
                }
                break;
            case 3:
                for (int j = 0; j < rSteps; j ++) {
                    yRot --;
                    draw3d(xRot, yRot);
                }
                break;
        }
    }
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

#define CONTROL_DEAD_ZONE 5 // THIS IS HARMLESS, BUT SUPERCEDED BY THE CUBIC FILTER
#define MAX_MOTOR_SPEED_CHANGE 25 // THIS SHOULD BE A LOWER NUMBER, LIKE 5
#define TASK_REFRESH_SPEED 20

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int frontLeftSpeed = 0, frontRightSpeed = 0, backLeftSpeed = 0, backRightSpeed = 0;

double filterInput(double input) {
    //if (std::abs(input) <= CONTROL_DEAD_ZONE) return 0;
    input = input * input * input / 10000;
    input = input * input * input / 10000;
    return input * input * input / 10000;
}

void adjustMotors(int xMove, int yMove, int wMove) {
    //double height2 = std::abs(filterInput(1750 - LiftMotor.rotation(vex::rotationUnits::deg))) / 1750;
    //Brain.Screen.printAt(0, 16, "%f", height2);
    double height = 1;

    int flMove = (yMove + xMove + wMove) * height;
    int frMove = (-yMove + xMove + wMove) * height;
    int blMove = (yMove - xMove + wMove) * height;
    int brMove = (-yMove - xMove + wMove) * height;

    // THIS SLEW CODE IS JUST AS BROKEN AS IT WAS LAST YEAR.  THINK IT THROUGH!   
    // IT ONLY GENERATES INCREMENTAL VALUES OF 25, AND CHANGES EVERY REFRESH BY +/- 25
    // IF THE DRIVER HOLDS A STEADY 77 (OR EVEN 75.0001) SIGNAL, THE OUTPUT WILL TOGGLE BETWEEN 75 AND 100 AT REFRESH RATE.
    // THIS IS VERY HARD TO DRIVE! YOU WANT TO CHECK IF THE REQUESTED CHANGE IS GRATER THAN THE SLEW, 
    // THEN EITHER PASS THROUGH THE CHANGE, OR REDUCE THAT CHANGE TO THE OLD VALUE +/- THE SLEW. 
    // 
    frontLeftSpeed += MAX_MOTOR_SPEED_CHANGE * (frontLeftSpeed < flMove ? 1 : -1);
    frontRightSpeed += MAX_MOTOR_SPEED_CHANGE * (frontRightSpeed < frMove ? 1 : -1);
    backLeftSpeed += MAX_MOTOR_SPEED_CHANGE * (backLeftSpeed < blMove ? 1 : -1);
    backRightSpeed += MAX_MOTOR_SPEED_CHANGE * (backRightSpeed < brMove ? 1 : -1);

    FrontLeftMotor.spin(vex::directionType::fwd, std::min(frontLeftSpeed, 100), vex::velocityUnits::pct);
    FrontRightMotor.spin(vex::directionType::fwd, std::min(frontRightSpeed, 100), vex::velocityUnits::pct);
    BackLeftMotor.spin(vex::directionType::fwd, std::min(backLeftSpeed, 100), vex::velocityUnits::pct);
    BackRightMotor.spin(vex::directionType::fwd, std::min(backRightSpeed, 100), vex::velocityUnits::pct);
}

int monitor() {
    Controller1.Screen.clearScreen(); // erase the default screen
    while (true) {
        // Code to monitor sensors or motors goes here

        vex::task::sleep(100);
    }
}

void usercontrol(void) {
    canSelectAuton = false;
    //drawNumbers();

    //vex::task monitorTask(monitor, vex::task::taskPriorityLow);
    vex::task screenUpdateTask(screenUpdate, vex::task::taskPrioritylow);
    
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
            LiftMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
        } else if (Controller1.ButtonL1.pressing() && !TopLimit.pressing()) {
            LiftMotor.spin(vex::directionType::fwd, -50, vex::velocityUnits::pct);
        } else if (Controller1.ButtonA.pressing()) {
            //Holodrive.driveFor(24, vex::distanceUnits::in, 0, 50, vex::velocityUnits::pct);
            autonomous();
        } else {
            LiftMotor.stop();
        }

        if (BottomLimit.pressing() && !Controller1.ButtonL1.pressing())
            LiftMotor.resetRotation();

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
    while (1) {
        vex::task::sleep(100); // Sleep the task for a short amount of time to prevent wasted resources.
    }
}
