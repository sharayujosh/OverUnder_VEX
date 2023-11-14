/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sharayu                                          */
/*    Created:      Fri Aug 11 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// CatapultMotor        motor         16              
// Inertial             inertial      17              
// BackArm              motor         20              
// ForwardRight         motor_group   9, 19           
// ForwardLeft          motor_group   8, 18           
// LimitSwitchC         limit         C               
// Claw                 motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "DriverControl.h"
#include "Autonomous.h"
#include "Drivetrain.h"
#include "Catapult.h"
#include "Flap.h"
#include "Settings.h"

using namespace vex;
competition Competition;
task driver;
task sensor;

Settings::ALLIANCE_TYPE Settings::alliance = Settings::ALLIANCE_TYPE::RED;
Settings::SKILLS_TYPE Settings::skills = Settings::SKILLS_TYPE::OFF;

void drawGUI(){
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 100, 500);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(120, 0, 100, 500);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(240, 0, 500, 500);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(250, 10, 80, 480);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(350, 0, 80, 480);
}

void selectAlliance(){
  int x = Brain.Screen.xPosition();
  if (x <=120) {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(0, 0, 100, 500);
    Settings::alliance = Settings::ALLIANCE_TYPE::RED;
    Settings::skills = Settings::SKILLS_TYPE::OFF;
  } else if (x <= 240) {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(0, 0, 100, 500);
    Settings::alliance = Settings::ALLIANCE_TYPE::BLUE;
    Settings::skills = Settings::SKILLS_TYPE::OFF;
  } else if (x <= 345) {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(0, 0, 100, 500);
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(10, 10, 80, 480);
    Settings::alliance = Settings::ALLIANCE_TYPE::RED;
    Settings::skills = Settings::SKILLS_TYPE::ON;
  } else if (x <= 450) {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(0, 0, 100, 500);
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(10, 10, 80, 480);
    Settings::alliance = Settings::ALLIANCE_TYPE::BLUE;
    Settings::skills = Settings::SKILLS_TYPE::ON;
  }

  Brain.Screen.setCursor(10, 10);
  Brain.Screen.print("15 Sec Auton 1");

  Brain.Screen.setCursor(240, 10);
  Brain.Screen.print("15 Sec Auton 2");

  Brain.Screen.setCursor(345, 10);
  Brain.Screen.print("Auto Skills");

  Brain.Screen.setCursor(450, 10);
  Brain.Screen.print("Driver Skills");
}

void armUp(){
  while(Controller1.ButtonR2.pressing()){
      BackArm.spin(forward);
  }
  BackArm.stop();
}

void armDown(){
  while(Controller1.ButtonR1.pressing()){
      BackArm.spin(reverse);
  }
  BackArm.stop();
}

void clawOut(){
  while(Controller1.ButtonL2.pressing()){
    Claw.spin(reverse);
  }
  Claw.stop();
}

void clawIn(){
  while(Controller1.ButtonL1.pressing()){
      Claw.spin(forward);
  }
  Claw.stop();
}

void automatedBeginning(){
  Catapult::retract();
  Drivetrain::turnToHeading(45, 20000);
  Drivetrain::driveForInches(12, 50000);
  Drivetrain::turnToHeading(-29, 20000);
  Drivetrain::driveForInches(6, 50000);
  Drivetrain::turnToHeading(-29, 20000);

  Catapult::flipReloadCatapult(15, 300);
}

// void usercontrol(){

//   while (1) {
//     DriverControl::getAxisChange();
//     wait(50, msec);
//   }
// }

void pre_auton(){
  Inertial.setHeading(0, degrees);
  drawGUI();
  Brain.Screen.pressed(selectAlliance);
  vex::wait(2000, msec);
}

void autonomous(){
  Autonomous::scoringAuton();
}

void usercontrol() {
  BackArm.setStopping(hold);
  Claw.setStopping(hold);
  BackArm.setVelocity(100, percent);
  Claw.setVelocity(70, percent);
  Catapult::retract();

  Controller1.ButtonA.pressed(Catapult::release);
  Controller1.ButtonB.pressed(Catapult::release);
  Controller1.ButtonUp.pressed(DriverControl::switchDir);

  Controller1.ButtonL2.pressed(clawOut);
  Controller1.ButtonL1.pressed(clawIn);

  Controller1.ButtonR1.pressed(armDown);
  Controller1.ButtonR2.pressed(armUp);
  
  while (true) {
    wait(10, msec);    
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  pre_auton();

  //headless testing
  //vex::wait(2000, msec);
  //autonomous();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while (true) {
    wait(200, msec);
  }
}