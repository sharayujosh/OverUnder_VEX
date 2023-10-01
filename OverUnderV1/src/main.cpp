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
// ForwardLeft          motor         1               
// ForwardRight         motor         2               
// CatapultMotor        motor         12              
// DigitalOutB          digital_out   B               
// DigitalOutC          digital_out   C               
// Inertial             inertial      15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "DriverControl.h"
#include "Drivetrain.h"
#include "Flap.h"
#include "Catapult.h"

using namespace vex;
competition Competition;
task driver;
task sensor;


// void catapult(){
//   CatapultMotor.setVelocity(100, percent);
//   CatapultMotor.spinFor(forward, 90, degrees);
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
  CatapultMotor.setVelocity(-20, percent);
  CatapultMotor.spin(forward);
  Controller1.ButtonA.pressed(Catapult::flipCatapult);
  Controller1.ButtonB.pressed(Flap::release);
  Controller1.ButtonX.pressed(Flap::engage);
  //Controller1.ButtonB.pressed(stopFlip);

  while (1) {
    DriverControl::getAxisChange();
    wait(50, msec);
  }
}

void prematchAuton(){
  Drivetrain::driveForInches(12, 50000);
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  //prematchAuton();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(prematchAuton);
}

