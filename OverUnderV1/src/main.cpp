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
// Catapult             motor         12              
// DigitalOutB          digital_out   B               
// DigitalOutC          digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Competition;
task driver;
task sensor;



void catapult(){
  Catapult.setVelocity(100, percent);
  Catapult.spinFor(forward, 90, degrees);
}

// void stopFlip(){
//   Catapult.setStopping(brake);
//   Catapult.stop();
// }

void release(){
  DigitalOutB.set(false);
  DigitalOutC.set(false);
}

void engage(){
  DigitalOutB.set(true);
  DigitalOutC.set(true);
}

void usercontrol(){
  Catapult.setVelocity(-10, percent);
  Catapult.spin(forward);
  Controller1.ButtonA.pressed(catapult);
  Controller1.ButtonB.pressed(release);
  Controller1.ButtonX.pressed(engage);
  //Controller1.ButtonB.pressed(stopFlip);
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Competition.drivercontrol(usercontrol);
}

