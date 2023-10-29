#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor CatapultMotor = motor(PORT16, ratio18_1, false);
inertial Inertial = inertial(PORT17);
motor BackArm = motor(PORT20, ratio18_1, false);
motor ForwardRightMotorA = motor(PORT9, ratio18_1, false);
motor ForwardRightMotorB = motor(PORT19, ratio18_1, false);
motor_group ForwardRight = motor_group(ForwardRightMotorA, ForwardRightMotorB);
motor ForwardLeftMotorA = motor(PORT8, ratio18_1, true);
motor ForwardLeftMotorB = motor(PORT18, ratio18_1, true);
motor_group ForwardLeft = motor_group(ForwardLeftMotorA, ForwardLeftMotorB);
limit LimitSwitchC = limit(Brain.ThreeWirePort.C);
motor Claw = motor(PORT6, ratio18_1, false);
controller Controller1 = controller(primary);

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