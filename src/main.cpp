// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "screen_draws.h"
#include "vex.h"

using namespace vex;

// Vars

bool solonoid = true;

// Mode Settings
int mode = 1;
int max = 3;

// Lift Lockout
int LiftLockout = 0;

// I DONT KNOW WHAT, BUT ITS IMPORTANT, DONT REMOVE
int value1 = 0;
int value2 = 0;
int value3 = 0;

// A global instance of competition
competition Competition;

/*                           Systems Declerations                          */

// Sensors
inertial Inertial1(PORT5);
triport TriSensors(PORT20);

limit PurpRotForward(TriSensors.A);
limit PurpRotReverse(TriSensors.B);

// triport ExpanderRight(PORT12);

// Controllers
controller Controller1(vex::controllerType::primary);
controller Controller2(vex::controllerType::partner);

// Drive motors
motor RearLeftDrive(PORT1, gearSetting::ratio18_1, true); // updated
motor FrontLeftDrive(PORT7, gearSetting::ratio18_1, true);
motor_group leftDrive(FrontLeftDrive, RearLeftDrive);
motor RearRightDrive(PORT10, gearSetting::ratio18_1, false); // updated
motor FrontRightDrive(PORT20, gearSetting::ratio18_1, false);
motor_group rightDrive(FrontRightDrive, RearRightDrive);

// General Motors
motor Mogoal(PORT9, gearSetting::ratio18_1, false); // updated

motor LiftMot(PORT3, gearSetting::ratio36_1, false); // updated
motor RiftMot(PORT4, gearSetting::ratio36_1, true);  // updated

motor_group LT(LiftMot, RiftMot);

motor capGoal(PORT15, gearSetting::ratio36_1, false); // thing on the lift

motor PurpRot(PORT19, gearSetting::ratio36_1, false); // lower intake

// Drive train
smartdrive DT(leftDrive, rightDrive, Inertial1, 299.24, 320, 40, mm, 1);

// Solonoid
digital_out valve = digital_out(Brain.ThreeWirePort.H);

/*---------------------------------------------------------------------------*/

/*                          Pre-Autonomous Functions                         */

void fullClear(void) {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
  Controller2.Screen.clearScreen();
}

void pre_auton(void) {
  Controller1.ButtonY.pressed(Small);
  valve.set(1);
  RiftMot.resetRotation();
  LiftMot.resetRotation();
  Mogoal.resetRotation();
  // Initializing Robot Configuration. DO NOT REMOVE! -- note, i will do what i
  // want.
  vexcodeInit();

  Inertial1.startCalibration(15);
  while (Inertial1.isCalibrating()) {
    Brain.Screen.setOrigin(3, 3);
    Brain.Screen.print("INITIATING MARK 2 B.F.R.");
    Brain.Screen.setOrigin(1, 1);
    Brain.Screen.print("CALIBRATING LOCATION IN TIME-SPACE CONTINUUM");
    Brain.Screen.setOrigin(5, 5);
    Brain.Screen.print("DONT TOUCH ME OR ILL SELF DESTRUCT");
  }
  fullClear();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Auton Selection");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Press X to bypass");
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("A for Big, Y for Small");

  Controller2.Screen.setCursor(1, 1);
  Controller2.Screen.print("Auton Selection");
  Controller2.Screen.setCursor(2, 1);
  Controller2.Screen.print("Press X to bypass");
  Controller2.Screen.setCursor(3, 1);
  Controller2.Screen.print("A for Big, Y for Small");
  //  Brain.Screen.clearScreen();
  allcolor();
  task::sleep(100);
  while (value1 == 0 && value2 == 0 && AutonSelection == 0) {
    /*
        Controller1.ButtonX.pressed(AutonBypass);
        Controller1.ButtonY.pressed(Small);
        Controller1.ButtonA.pressed(Big);

        Controller2.ButtonX.pressed(AutonBypass);
        Controller2.ButtonY.pressed(Small);
        Controller2.ButtonA.pressed(Big);
    */
    int xPos = Brain.Screen.xPosition();
    int yPos = Brain.Screen.yPosition();
    if (Brain.Screen.pressing()) {
      if (xPos <= 160) {
        if (yPos <= 136 && yPos >= 32) {
          Brain.Screen.clearScreen();
          BigRed();
          AutonSelection = 1;
        }
        if (yPos >= 136) {
          Brain.Screen.clearScreen();
          SmallRed();
          AutonSelection = 4;
        }
      }
      if (xPos >= 160 && xPos <= 320) {
        if (yPos <= 136) {
          Brain.Screen.clearScreen();
          BigBlue();
          AutonSelection = 2;
        }
        if (yPos >= 136) {
          Brain.Screen.clearScreen();
          SmallBlue();
          AutonSelection = 5;
        }
      }
      if (xPos >= 320) {
        if (yPos <= 136) {
          Brain.Screen.clearScreen();
          Skills();
          AutonSelection = 3;
        }
        if (yPos >= 136) {
          Brain.Screen.clearScreen();
          NoAuton();
          AutonSelection = 6;
        }
      }
    } else {
    }
    // Brain.Screen.render();
  }
  Brain.Screen.setOrigin(1, 1);
  Controller1.Screen.setCursor(1, 1);
  Controller2.Screen.setCursor(1, 1);
  Controller1.Screen.clearScreen();
  Controller2.Screen.clearScreen();
  Controller1.Screen.print("INITIATING");
  Controller1.Screen.newLine();
  Controller1.Screen.print("MARK 2");
  Controller1.Screen.newLine();
  Controller1.Screen.print("BIG F***ING ROBOT");
  Controller2.Screen.print("WELCOME");
  Controller2.Screen.newLine();
  Controller2.Screen.print("TO THE");
  Controller2.Screen.newLine();
  Controller2.Screen.print("RICEFIELDS");
  task::sleep(100);
}

void BrainScreenUpdate(int CurrentMode) {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Mode: ", CurrentMode);
  Brain.Screen.newLine();
  if (CurrentMode == 1) {
    // Brain.Screen.newLine();
    Brain.Screen.print("Full Speed");
  } else if (CurrentMode == 2) {
    // Brain.Screen.newLine();
    Brain.Screen.print("Half Speed");
  } else if (CurrentMode == 3) {
    // Brain.Screen.newLine();
    Brain.Screen.print("Quarter Speed");
  }
  Brain.Screen.print(Brain.Battery.capacity()); //"Bat: %f",
}
void ConsScreenUpdate(int CurrentMode) {

  Controller1.Screen.setCursor(1, 1);

  Controller2.Screen.setCursor(1, 1);

  if (CurrentMode == 1) {
    Controller1.Screen.print("Full Speed");
    Controller2.Screen.print("Full Speed");
  } else if (CurrentMode == 2) {
    Controller1.Screen.print("Half Speed");
    Controller2.Screen.print("Half Speed");
  } else if (CurrentMode == 3) {
    Controller1.Screen.print("Quarter Speed");
    Controller2.Screen.print("Quarter Speed");
  }
  Controller1.Screen.newLine();
  Controller1.Screen.print(Brain.Battery.capacity()); //"Bat: %f",
  Controller2.Screen.newLine();
  Controller2.Screen.print(Brain.Battery.capacity()); //"Bat: %f",
  Controller1.Screen.newLine();
  Controller1.Screen.newLine();
}

void toggleSolonoid(void) {
  if (valve.value() == 0) {
    valve.set(1);
  } else if (valve.value() == true) {
    valve.set(0);
  }
}

void modeInc(void) {
  mode = mode + 1;

  if (mode == max + 1) {
    mode = 1;
  }
  fullClear();
  ConsScreenUpdate(mode);
  BrainScreenUpdate(mode);
}

void modeDec(void) {
  mode = mode - 1;

  if (mode == 0) {
    mode = max;
  }
  fullClear();
  ConsScreenUpdate(mode);
  BrainScreenUpdate(mode);
}

bool isWithin(double start, double end, double num) {
  if (start <= num) {
    if (num <= end) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
  // isWithin(start,end,num,0,0);
}
bool isWithin(double start, double end, double num, double buffer,
              int bufferType) {
  // 0 = no buffer. 1 = inside the start. 2 = outside the start. 3 = inside the
  // end. 4 = outside the end.
  double buffS = 0;
  double buffE = 0;
  if (bufferType == 1) {
    buffS = buffer;
  } else if (bufferType == 2) {
    buffS = -buffer;
  } else if (bufferType == 3) {
    buffE = -buffer;
  } else if (bufferType == 4) {
    buffE = buffer;
  }

  if (start + buffS <= num) {
    if (num <= end + buffE) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

/* Supplemental functions*/

int riftTo1k(void) {
  RiftMot.rotateTo(-500, rotationUnits::deg);
  return (0);
}

int liftTo1k(void) {
  LiftMot.rotateTo(500, rotationUnits::deg);
  return (0);
}

int spinNew(void) {
  PurpRot.spin(fwd, 40, pct);
  wait(4, sec);
  PurpRot.stop();
  return (0);
}

/*    AUTON TASKS    */

void smallAuto(std::string loc) {
  if (loc == "skillz") {
    toggleSolonoid();
    capGoal.setStopping(hold);
    capGoal.spinTo(270, rotationUnits::deg, false);
    DT.driveFor(4.6 * 12, distanceUnits::in, 100, velocityUnits::pct);
    DT.driveFor(0.3 * 12, distanceUnits::in, 30, velocityUnits::pct);
    capGoal.spinTo(0, rotationUnits::deg, true);
    capGoal.stop(brake);
    LT.spinTo(300, deg, false);
    DT.driveFor(-3.25 * 12, distanceUnits::in, 60, velocityUnits::pct);
    DT.turnToRotation(-90, rotationUnits::deg, 35, velocityUnits::pct);
    DT.driveFor(-1.80 * 12, distanceUnits::in, false);
    wait(2.5, sec);
    toggleSolonoid();
    PurpRot.spin(fwd, 40, pct);
    DT.driveFor(1.75 * 12, distanceUnits::in);
    wait(4, sec);
    PurpRot.stop();
    DT.turnToRotation(0, deg);
    DT.driveFor(8 * 12, distanceUnits::in);
    LT.spinTo(0, deg);
    DT.driveFor(-0.3 * 12, distanceUnits::in);
    DT.turnToRotation(-90, deg);
    DT.driveFor(-0.5 * 12, distanceUnits::in);
    toggleSolonoid();
    DT.driveFor(6 * 12, distanceUnits::in);
  } else if (loc == "blue" || loc == "red") {
    toggleSolonoid();
    capGoal.setStopping(hold);
    capGoal.spinTo(270, rotationUnits::deg, false);
    DT.driveFor(4.6 * 12, distanceUnits::in, 100, velocityUnits::pct);
    DT.driveFor(0.3 * 12, distanceUnits::in, 40, velocityUnits::pct);
    capGoal.spinTo(0, rotationUnits::deg, true);
    capGoal.stop(brake);
    LT.spinTo(300, deg, false);
    DT.driveFor(-3.25 * 12, distanceUnits::in, 60, velocityUnits::pct);
    DT.turnToRotation(-90, rotationUnits::deg, 35, velocityUnits::pct);
    DT.driveFor(-1.80 * 12, distanceUnits::in, false);
    wait(2.5, sec);
    toggleSolonoid();
    PurpRot.spin(fwd, 40, pct);
    DT.driveFor(1.75 * 12, distanceUnits::in);
    wait(4, sec);
    PurpRot.stop();
  }
}

void bigAuto(std::string loc) {
  if (loc == "blue") {
    toggleSolonoid();
    LT.spinTo(300, deg, false);
    DT.driveFor(-0.5*12, distanceUnits::in);
    toggleSolonoid();
    PurpRot.spin(fwd, 65, pct);
    wait(4, sec);
    PurpRot.stop();
    DT.driveFor(0.5*12, distanceUnits::in);
  } else if ( loc == "red") {
    //DT.driveFor(3.5*12, distanceUnits::in);
    LT.spinTo(300, deg, false);
  }
}

/*                              Autonomous Task                              */

void autonomous(void) {
  if (AutonSelection == 5 || AutonSelection == 4) { // Small Blue and Small Red
    smallAuto("blue");
  } else if (AutonSelection == 1 ||
             AutonSelection == 2) { // Big Blue and Big Red
    bigAuto("blue");
  } else if (AutonSelection == 3) {
    smallAuto("skillz");
  }
}

/*                              User Control Task                            */

void usercontrol(void) {
  if (Controller1.installed()) {
    fullClear();
    ConsScreenUpdate(mode);
    BrainScreenUpdate(mode);
  }
  while (1) { // Main exec loop
    wait(20, msec);

    //-----------------\/
    //                 \/
    //  Pilot Controls \/
    //                 \/
    //-----------------\/
    //    if (Controller1.ButtonL2.pressing() /*&&
    //        isWithin(-15, 350, Mogoal.rotation(deg))*/) {
    //      Mogoal.spin(directionType::rev, 50, pct);
    //    } else if (Controller1.ButtonL1.pressing() /* &&
    //               isWithin(-15, 350, Mogoal.rotation(deg)) */) {
    //      Mogoal.spin(directionType::fwd, 50, pct);
    //    } else {
    //      Mogoal.stop(brake);
    //    }

    if (Controller1.ButtonR1.pressing() /* &&
        isWithin(-1500, 30, RiftMot.rotation(deg)) &&
        isWithin(-30, 1500, LiftMot.rotation(deg)) */) {
      RiftMot.spin(directionType::fwd, 75, pct);
      LiftMot.spin(directionType::fwd, 75, pct);
    } else if (Controller1.ButtonR2.pressing() /* &&
               isWithin(-1500, 30, RiftMot.rotation(deg)) &&
               isWithin(-30, 1500, LiftMot.rotation(deg)) */) {
      RiftMot.spin(directionType::rev, 75, pct);
      LiftMot.spin(directionType::rev, 75, pct);
    } else {
      RiftMot.stop(brake);
      LiftMot.stop(brake);
    }

    if (Controller1.ButtonL1.pressing()) {
      capGoal.spin(directionType::fwd, 75, pct);
    } else {
      capGoal.stop(coast);
    }

    if (Controller1.ButtonA.pressing()) {
      PurpRot.spin(directionType::rev, 75, pct);
    } else if (Controller1.ButtonB.pressing()) {
      PurpRot.spin(directionType::fwd, 75, pct);
    } else {
      PurpRot.stop(brake);
    }

    // Drive controls serperated into modes
    if (mode == 1) {
      rightDrive.spin(directionType::fwd, Controller1.Axis2.value(), pct);
      leftDrive.spin(directionType::fwd, Controller1.Axis3.value(), pct);
    } else if (mode == 2) {
      rightDrive.spin(directionType::fwd, Controller1.Axis2.value() / 2, pct);
      leftDrive.spin(directionType::fwd, Controller1.Axis3.value() / 2, pct);
    } else if (mode == 3) {
      rightDrive.spin(directionType::fwd, Controller1.Axis2.value() / 4, pct);
      leftDrive.spin(directionType::fwd, Controller1.Axis3.value() / 4, pct);
    }
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  Controller1.ButtonDown.pressed(modeDec);
  Controller1.ButtonUp.pressed(modeInc);
  Controller1.ButtonL2.pressed(toggleSolonoid);

  // wowowowow comment go brrrrrrrrr

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
