using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor CatapultMotor;
extern inertial Inertial;
extern motor BackArm;
extern motor_group ForwardRight;
extern motor_group ForwardLeft;
extern limit LimitSwitchC;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );