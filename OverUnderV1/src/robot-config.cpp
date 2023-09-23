#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ForwardLeft = motor(PORT1, ratio18_1, false);
motor ForwardRight = motor(PORT2, ratio18_1, true);
motor CatapultMotor = motor(PORT12, ratio18_1, false);
digital_out DigitalOutB = digital_out(Brain.ThreeWirePort.B);
digital_out DigitalOutC = digital_out(Brain.ThreeWirePort.C);
inertial Inertial = inertial(PORT15);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}