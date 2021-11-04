#include "vex.h"
using namespace vex;
brain Brain;

/*Screen Buttons*/

int AutonSelection = 0;
int SquareX = 160;
int SquareY = 122;
void BigRed() {
  Brain.Screen.setFillColor("#ff0000");
  Brain.Screen.drawRectangle(0, 0, SquareX, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.setPenWidth(2);
  Brain.Screen.printAt(56, 57, "Big");
  Brain.Screen.printAt(53, 96, "Red");
}
void BigBlue() {
  Brain.Screen.setFillColor("#0000ff");
  Brain.Screen.drawRectangle(160, 0, SquareX, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.printAt(217, 57, "Big");
  Brain.Screen.printAt(210, 96, "Blue");
}
void Skills() {
  Brain.Screen.setFillColor("#ff00ff");
  Brain.Screen.drawRectangle(320, 0, SquareX, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.printAt(365, 75, "Skills");
}
void SmallRed() {
  Brain.Screen.setFillColor("#ff0000");
  Brain.Screen.drawRectangle(0, 122, SquareX, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.printAt(41, 180, "Small");
  Brain.Screen.printAt(50, 210, "Red");
}
void SmallBlue() {
  Brain.Screen.setFillColor("#0000ff");
  Brain.Screen.drawRectangle(160, 122, SquareX, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.printAt(205, 180, "Small");
  Brain.Screen.printAt(210, 210, "Blue");
}
void NoAuton() {
  Brain.Screen.setFillColor("#000000");
  Brain.Screen.drawRectangle(320, 122, 160, SquareY);
  Brain.Screen.setFont(fontType::prop30);
  Brain.Screen.printAt(380, 181, "No");
  Brain.Screen.printAt(360, 212, "Auton");
}
void AutonBypass(void) {
      Brain.Screen.clearScreen();
      NoAuton();
      AutonSelection = 6;
}
void Small(void) {
  Brain.Screen.clearScreen();
  SmallBlue();
  AutonSelection = 5;
}
void Big(void) {
  Brain.Screen.clearScreen();
  BigBlue();
  AutonSelection = 2;
}

void allcolor() {
  BigRed();
  BigBlue();
  Skills();
  SmallRed();
  SmallBlue();
  NoAuton();
}