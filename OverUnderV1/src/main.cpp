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
Settings::AUTO_MATCH_TYPE Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::NONE;

void drawGUI(){
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 100, 500);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(90, 0, 100, 500);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(180, 0, 100, 500);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(270, 0, 100, 500);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(360, 0, 100, 500);

  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("Descore");

  Brain.Screen.setCursor(5, 10);
  Brain.Screen.print("Score");

  Brain.Screen.setCursor(6, 20);
  Brain.Screen.print("Auto Skills");

  Brain.Screen.setCursor(7, 30);
  Brain.Screen.print("none");

  Brain.Screen.setCursor(8, 40);
  Brain.Screen.print("Driver Skills");
}

void selectAlliance(){
  int x = Brain.Screen.xPosition();
  if (x <=90) {
    // descore
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(0, 0, 100, 500);
    Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::DESCORE;
  } else if (x <= 180) {
    // score
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(90, 0, 100, 500);
    Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::SCORE;
  } else if (x <= 270) {
    // auto skills
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(180, 0, 100, 500);
    Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::AUTO_SKILLS;
  } else if (x <= 360) {
    // none
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(270, 0, 100, 500);
    Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::NONE;
  } else if (x <= 450) {
    // none
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(360, 0, 100, 500);
    Settings::autoMatchType = Settings::AUTO_MATCH_TYPE::DRIVER_SKILLS;
  }
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
  Drivetrain::turnToHeading(-27, 20000);
  vex::wait(800, msec);
  Catapult::flipReloadCatapult(15, 300);
}

void pre_auton(){
  Inertial.setHeading(0, degrees);
  drawGUI();
  Brain.Screen.pressed(selectAlliance);
  vex::wait(2000, msec);
}

void autonomous(){
  switch (Settings::autoMatchType) {
    case Settings::AUTO_SKILLS:
      Autonomous::autoSkills();
      break;
    case Settings::DESCORE:
      Autonomous::descoreAuton();
      break;
    case Settings::SCORE:
      Autonomous::scoringAuton();
      break;
    default:
      break;

  }
}

void usercontrol() {
  if (Settings::autoMatchType == Settings::AUTO_SKILLS){
    Autonomous::autoSkills();
  }

  if (Settings::autoMatchType == Settings::DRIVER_SKILLS){
    automatedBeginning();
  }

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
    DriverControl::getAxisChange();
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