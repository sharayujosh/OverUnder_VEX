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
#include "Drivetrain.h"
#include "Flap.h"

using namespace vex;
competition Competition;
task driver;
task sensor;

void usercontrol(){

  //Controller1.ButtonB.pressed(stopFlip);

  while (1) {
    DriverControl::getAxisChange();
    wait(50, msec);
  }
}

void prematchAuton(){
  Drivetrain::driveForInches(12, 50000);
}

void retract(){
  CatapultMotor.setStopping(hold);
  CatapultMotor.setVelocity(90, percent);
  CatapultMotor.spin(forward);

  while(!LimitSwitchC.pressing()){
    wait(10, msec);
  }

  CatapultMotor.stop();
}
void release(){
  CatapultMotor.setStopping(coast);
  CatapultMotor.setVelocity(30, percent);
  CatapultMotor.spin(forward);
  wait(500, msec);
  CatapultMotor.stop();
}

void armUp(){
  //BackArm.spinFor(forward, 70, degrees);
  while(Controller1.ButtonR2.pressing()){
      BackArm.spin(forward);
  }
  BackArm.stop();
}

void armDown(){
  //BackArm.spinFor(reverse, 70, degrees);
  while(Controller1.ButtonR1.pressing()){
      BackArm.spin(reverse);
  }
  BackArm.stop();
}

void clawOut(){
  // Claw.spin(reverse);
  // wait(500, msec);
  // Claw.stop();
  while(Controller1.ButtonL2.pressing()){
    Claw.spin(reverse);
  }
  Claw.stop();
  //Claw.spinFor(reverse, 50, degrees);
}

void clawIn(){
  // Claw.spin(forward);
  // wait(500, msec);
  // Claw.stop();
  while(Controller1.ButtonL1.pressing()){
      Claw.spin(forward);
  }
  Claw.stop();
  // Claw.spinFor(forward, 50, degrees);
}

void scoringAuton(){
  retract();
  Claw.spinFor(reverse, 200, degrees);
  Drivetrain::driveForInches(44, 50000);
  Claw.spinFor(forward, 200, degrees);
  Drivetrain::driveForInches(-35, 50000);
  Drivetrain::turnToHeading(300, 20000);
  release();
  Drivetrain::driveForInches(-52, 50000);
}

int main() {
  Inertial.setHeading(0, degrees);
  vex::wait(2000, msec);

  // scoringAuton();

  // Drivetrain::driveForInches(-12, 50000);
  // Drivetrain::turnToHeading(90, 5000);

  BackArm.setStopping(hold);
  Claw.setStopping(hold);
  BackArm.setVelocity(70, percent);
  Claw.setVelocity(70, percent);

  Controller1.ButtonA.pressed(retract);
  Controller1.ButtonB.pressed(release);

  Controller1.ButtonL2.pressed(clawOut);
  Controller1.ButtonL1.pressed(clawIn);

  Controller1.ButtonR1.pressed(armDown);
  Controller1.ButtonR2.pressed(armUp);
  
  while (true) {
    wait(10, msec);    
  }
}

