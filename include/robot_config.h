// h

vex::brain Brain;
vex::motor FrontLeftMotor(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor FrontRightMotor(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor BackLeftMotor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor BackRightMotor(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LiftMotor1(vex::PORT7, vex::gearSetting::ratio18_1, false);
vex::motor LiftMotor2(vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor GrabMotor(vex::PORT12, vex::gearSetting::ratio18_1, false);
vex::controller Controller1;
vex::competition Competition;
vex::holodrive Holodrive(&FrontLeftMotor, &FrontRightMotor, &BackLeftMotor, &BackRightMotor, 2.75, vex::distanceUnits::in);
vex::motor_group LiftMotor(LiftMotor1, LiftMotor2);
vex::bumper TopLimit(Brain.ThreeWirePort.A);
vex::bumper BottomLimit(Brain.ThreeWirePort.B);
threedee ThreeDee;