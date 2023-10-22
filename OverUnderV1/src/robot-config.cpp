#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor CatapultMotor = motor(PORT16, ratio18_1, false);
inertial Inertial = inertial(PORT15);
motor BackArm = motor(PORT20, ratio18_1, false);
motor ForwardRightMotorA = motor(PORT9, ratio18_1, false);
motor ForwardRightMotorB = motor(PORT19, ratio18_1, false);
motor_group ForwardRight = motor_group(ForwardRightMotorA, ForwardRightMotorB);
motor ForwardLeftMotorA = motor(PORT8, ratio18_1, true);
motor ForwardLeftMotorB = motor(PORT18, ratio18_1, true);
motor_group ForwardLeft = motor_group(ForwardLeftMotorA, ForwardLeftMotorB);
limit LimitSwitchC = limit(Brain.ThreeWirePort.C);
motor Claw = motor(PORT6, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Claw
      if (Controller1.ButtonL1.pressing()) {
        Claw.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Claw.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Claw.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control BackArm
      if (Controller1.ButtonR1.pressing()) {
        BackArm.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        BackArm.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        BackArm.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}