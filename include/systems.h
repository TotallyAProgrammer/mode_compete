using namespace vex;

// Controllers
controller Controller1(vex::controllerType::primary);
//controller Controller2(vex::controllerType::partner);

// Drive motors
motor  leftDrive(PORT1,  gearSetting::ratio18_1, false);
motor rightDrive(PORT10, gearSetting::ratio18_1, true);
