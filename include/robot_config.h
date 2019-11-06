// h

vex::brain Brain;
vex::motor FrontLeftMotor(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor FrontRightMotor(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor BackLeftMotor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor BackRightMotor(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LiftMotor(vex::PORT5, vex::gearSetting::ratio18_1, false);
vex::motor GrabMotor(vex::PORT6, vex::gearSetting::ratio18_1, false);
vex::controller Controller1;
vex::competition Competition;
vex::holodrive Holodrive(&FrontLeftMotor, &FrontRightMotor, &BackLeftMotor, &BackRightMotor);
vex::bumper TopLimit(Brain.ThreeWirePort.A);
vex::bumper BottomLimit(Brain.ThreeWirePort.B);