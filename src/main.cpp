// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "screen_draws.h"
#include "vex.h"

using namespace vex;

// Vars

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
triport ExpanderLeft(PORT11);
triport ExpanderRight(PORT12);

// Controllers
controller Controller1(vex::controllerType::primary);
controller Controller2(vex::controllerType::partner);

// Drive motors
motor leftDrive(PORT1, gearSetting::ratio18_1, false);
motor rightDrive(PORT10, gearSetting::ratio18_1, true);

// General Motors
motor Mogoal(PORT8, gearSetting::ratio18_1, false);

// Drive train
smartdrive DT(leftDrive, rightDrive, Inertial1, 299.24, 320, 40, mm, 1);

// LED Setup
led l1(ExpanderLeft.A);
led l2(ExpanderLeft.B);
led l3(ExpanderLeft.C);
led l4(ExpanderLeft.D);
led l5(ExpanderLeft.E);
led l6(ExpanderLeft.F);
led l7(ExpanderLeft.G);
led l8(ExpanderLeft.H);

led r1(ExpanderRight.A);
led r2(ExpanderRight.B);
led r3(ExpanderRight.C);
led r4(ExpanderRight.D);
led r5(ExpanderRight.E);
led r6(ExpanderRight.F);
led r7(ExpanderRight.G);
led r8(ExpanderRight.H);


void ledVisual(void) {
  if (mode == 3) {}
}


/*                          Pre-Autonomous Functions                         */

void fullClear(void) {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
  Controller2.Screen.clearScreen();
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE! -- note, i will do what i
  // want.
  vexcodeInit();

  Inertial1.startCalibration(10);
  while (Inertial1.isCalibrating()) {
    Brain.Screen.setOrigin(1, 1);
    Brain.Screen.print("CALIBRATING LOCATION IN TIME-SPACE CONTINUUM");
  }
  fullClear();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Auton Selection");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Press X to bypass");
  Controller2.Screen.setCursor(1, 1);
  Controller2.Screen.print("Auton Selection");
  Controller2.Screen.setCursor(2, 1);
  Controller2.Screen.print("Press X to bypass");
  //  Brain.Screen.clearScreen();
  allcolor();
  task::sleep(100);
  while (value1 == 0 && value2 == 0 && AutonSelection == 0) {
    Controller1.ButtonX.pressed(AutonBypass);
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
  Controller1.Screen.print("WELCOME");
  Controller1.Screen.newLine();
  Controller1.Screen.print("TO THE");
  Controller1.Screen.newLine();
  Controller1.Screen.print("RICEFIELDS");
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
}

void smallAuto(std::string loc) {
  if (loc == "blue" || loc == "red") {
    DT.driveFor(9.7, distanceUnits::in);
    DT.turnToRotation(90, rotationUnits::deg);
    DT.driveFor(67, distanceUnits::in);
  }
}

void bigAuto(std::string loc) {
  if (loc == "blue" || loc == "red") {
    DT.driveFor(24, distanceUnits::in);
    DT.turnToRotation(45, rotationUnits::deg);
    DT.driveFor(12, distanceUnits::in);
    DT.turnToRotation(360, rotationUnits::deg);
  }
}

/*                              Autonomous Task                              */

void autonomous(void) {
  if (AutonSelection == 5 || AutonSelection == 4) { //Small Blue and Small Red
    smallAuto("blue");
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
    /*if (Controller1.ButtonA.pressing() || Controller1.ButtonB.pressing() ||
        Controller1.ButtonX.pressing() || Controller1.ButtonY.pressing() ||
        Controller1.ButtonR1.pressing() ||
        Controller1.ButtonR2.pressing()) {
      Brain.Screen.setOrigin(1, 1);
      Brain.Screen.clearScreen();
      Controller1.Screen.clearLine(1);
      Controller1.Screen.clearLine(2);
      Controller2.Screen.clearLine(1);
      Controller2.Screen.clearLine(2);
      BrainScreenUpdate(mode);
      ConsScreenUpdate(mode);
    }*/
    Controller1.ButtonR2.pressed(modeDec);
    Controller1.ButtonR1.pressed(modeInc);


    //-----------------\/
    //                 \/
    //  Pilot Controls \/
    //                 \/
    //-----------------\/
    if (Controller1.ButtonL2.pressing() &&
        isWithin(-340, 10, Mogoal.rotation(deg))) {
      Mogoal.spin(directionType::rev, 50, pct);
    } else if (Controller1.ButtonL1.pressing() &&
               isWithin(-340, 10, Mogoal.rotation(deg))) {
      Mogoal.spin(directionType::fwd, 50, pct);
    } else {
      Mogoal.stop(brake);
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

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
