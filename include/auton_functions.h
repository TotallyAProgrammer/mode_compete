#include "vex.h"
#include "systems.h"

using namespace vex;


void Driving(int Distance, int Speed) {
  Drivetrain.setDriveVelocity(Speed, percent);
  Drivetrain.driveFor(Distance, inches);
}
/*void Turning(int TurnAngle, int Speed) {
  Drivetrain.setHeading(0, degrees);
  Drivetrain.setTurnVelocity(Speed, pct);
  Drivetrain.turnToHeading(TurnAngle, degrees);
}*/
void Turning(int TurnAngle, int Speed) {
  Drivetrain.setTurnVelocity(Speed, pct);
  Drivetrain.turnFor(TurnAngle, degrees);
}
void ClawClose(void) {
  Claw.spin(directionType::fwd, 50, pct);
  task::sleep(700);
  Claw.setStopping(hold);
  Claw.stop();
}
void ClawOpen(void) {
  Claw.spin(directionType::rev, 50, pct);
  task::sleep(700);
  Claw.setStopping(hold);
  Claw.stop();
}
void DriveUntil(bool Condition, int Speed){
  while(Condition == false){
      Drivetrain.setDriveVelocity(Speed, percent);
      Drivetrain.drive(forward);
  }
  Drivetrain.stop();
}
void PrintMode(int size, int side) { //std::string size,std::string side
  Brain.Screen.clearScreen();
  if(side==0){//No
    Brain.Screen.setFillColor("#000000"); 
  }else if(side==1){//Red
    Brain.Screen.setFillColor("#ff0000");
  }else if(side==2){//Blue
    Brain.Screen.setFillColor("#0000ff"); 
  }else if(side==4){//Skills
    Brain.Screen.setFillColor("#ff00ff");
  }
  //
  Brain.Screen.drawRectangle(0, 0, 480, 272);
  Brain.Screen.setFont(fontType::mono40);
  Brain.Screen.setPenWidth(2);
  if(size==0){//No
    Brain.Screen.printAt((240-(2*10)), (272/2-43), "No" ); //"%f", size
  }else if(size==1){//Small
    Brain.Screen.printAt((240-(5*10)), (272/2-43), "Small" ); //"%f", size
  }else if(size==2){//Big
    Brain.Screen.printAt((240-(3*10)), (272/2-43), "Big" ); //"%f", size
  }else{//Skills  
    Brain.Screen.printAt((240-(6*10)), (272/2-43), "Skills" ); //"%f", size
  }
  if(side==0){//No
    Brain.Screen.printAt((240-(5*10)), ((272/2)+3), "Auton" ); 
  }else if(side==1){//Red
    Brain.Screen.printAt((240-(3*10)), ((272/2)+3), "Red" ); 
  }else if(side==2){//Blue
    Brain.Screen.printAt((240-(4*10)), ((272/2)+3), "Blue" ); 
  }else{
    Brain.Screen.printAt((240-(3*10)), ((272/2)+3), "Run" );
  }
  
}

void auton1() { /*Auton Red Big*/
  ClawClose();
  Driving(4, 50);
  Turning(70, 50);
  task::sleep(100);
  Driving(20, 50);
  ClawOpen();
  Driving(-19, 50);
  Turning(-80, 50);
}
void auton2() { /*Auton Blue Big*/
  ClawClose();
  /*Driving(2, 50);
  Turning(-70, 50);
  task::sleep(100);
  Driving(20, 50);
  ClawOpen();
  Driving(-19, 50);
  Turning(70, 50);
  DriveUntil((BumperC.pressing() && BumperD.pressing()), -50);*/
  Driving(20,50);
  task::sleep(100);
  ClawOpen();
  Driving(-18,50);
  Turning(70,50);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Aligning");
  //DriveUntil((BumperC.pressing() && BumperD.pressing()), -50);
  task::sleep(100);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Done");
  Driving(20,50);
}
void auton3() { /*Auton Skills*/
  auton2();
}
void auton4() { /*Auton Red Little*/
  Driving(20, 60);
  Driving(-20, 60);
  //Turning(80, 50);
}
void auton5() { /*Auton Blue Little*/
  Driving(20, 60);
  Driving(-20, 60);
  //Turning(-80, 50);
}
void auton6() { /*Auton None*/}
