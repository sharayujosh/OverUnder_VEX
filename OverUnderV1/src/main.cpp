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
// Controller1          controller                    
// CatapultMotor        motor         16              
// Inertial             inertial      15              
// BackArm              motor         20              
// ForwardRight         motor_group   9, 19           
// ForwardLeft          motor_group   8, 18           
// LimitSwitchC         limit         C               
// Claw                 motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "DriverControl.h"
#include "Drivetrain.h"
#include "Flap.h"

using namespace vex;
competition Competition;
task driver;
task sensor;


// void CatapultMotorpult(){
//   CatapultMotorpultMotor.setVelocity(100, percent);
//   CatapultMotorpultMotor.spinFor(forward, 90, degrees);
// }

// void release(){
//   DigitalOutB.set(false);
//   DigitalOutC.set(false);
// }

// void engage(){
//   DigitalOutB.set(true);
//   DigitalOutC.set(true);
// }

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
  CatapultMotor.setVelocity(70, percent);
  CatapultMotor.spin(forward);

  while(!LimitSwitchC.pressing()){
    wait(10, msec);
  }

  CatapultMotor.stop();
}

void release(){
  CatapultMotor.setStopping(coast);
  CatapultMotor.setVelocity(20, percent);
  CatapultMotor.spin(forward);
  wait(500, msec);
  CatapultMotor.stop();
}

void armUp(){
  BackArm.spin(forward);
}

void armDown(){
  BackArm.spin(reverse);
}

void clawOut(){
  Claw.spin(reverse);
}

void clawIn(){
  Claw.spin(forward);
}

int main() {
  BackArm.setStopping(hold);
  Claw.setStopping(hold);
  BackArm.setVelocity(70, percent);
  Claw.setVelocity(70, percent);

  Controller1.ButtonA.pressed(retract);
  Controller1.ButtonB.pressed(release);

  // Controller1.ButtonL1.pressed(clawOut);
  // while(Controller1.ButtonL1.pressing()){
  //   clawOut();
  // }
  // while(Controller1.ButtonL2.pressing()){
  //   clawIn();
  // }
  // Controller1.ButtonL2.pressed(clawIn);

  // Controller1.ButtonR1.pressed(armUp);
  // Controller1.ButtonR2.pressed(armDown);
  
  while (true) {
    wait(10, msec);    
  }
}

