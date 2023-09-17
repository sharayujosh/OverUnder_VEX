#include "DriverControl.h"
#include "vex.h"
#include "Pid.h"
#include "math.h"

namespace DriverControl{

  static int prevAxis1 = 0;
  static int prevAxis2 = 0;
  static int prevAxis3 = 0;
  static int prevAxis4 = 0;

  void getAxisChange(){
    int axis3 = Controller1.Axis3.position(percent);
    int axis4 = Controller1.Axis4.position(percent);
    int axis1 = Controller1.Axis1.position(percent);
    int axis2 = Controller1.Axis2.position(percent);

    int maxVel = 100;

    if (!(prevAxis1 == axis1 && prevAxis2 == axis2 && prevAxis3 == axis3 && prevAxis4 == axis4)){
      // switch (Settings::drivetrainType) {
      // case Settings::XDRIVE:
      //   //computeRelativeMotion(axis3, axis4, axis1, axis2, maxVel);
      //   combineDriveAndSpinMotionXDrive(axis3, axis4, axis1, axis2, maxVel);
      //   break;
      // case Settings::STANDARD_DRIVE:
      //   // switched 1 and 4 
        combineDriveAndSpinMotionStandardDrive(axis3, axis1, axis4, axis2, maxVel);
        //break;
      //}
    }

    prevAxis1 = axis1;
    prevAxis2 = axis2;
    prevAxis3 = axis3;
    prevAxis4 = axis4;
  }

  // void combineDriveAndSpinMotionXDrive(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer){
  //   const int deadband = 10;
  //   const double factor = 100;
  //   const double turningFactor = 60; // edit max turning velocity
  //   axis4 = axis4/turningFactor;
  //   // square axis value and divide by 100

    
  //   int upDown = (abs(axis3) < deadband) ? 0:axis3*abs(axis3)/factor;
  //   int leftRight = (abs(axis4) < deadband) ? 0:axis4*abs(axis4)/factor;
  //   int turning = (abs(axis1) < deadband) ? 0:axis1*abs(axis1)/factor;

  //   float sum = abs(upDown) + abs(leftRight) + abs(turning);

  //   if (sum > maxVelocityPer){
  //     const float ratio = maxVelocityPer/sum;
  //     upDown *= ratio;
  //     leftRight *= ratio;
  //     turning *= ratio;
  //   }

  //   const double FLMotorVel = -(upDown + leftRight - turning);
  //   const double FRMotorVel = upDown - leftRight + turning;
  //   const double BLMotorVel = -(upDown - leftRight - turning);
  //   const double BRMotorVel = upDown + leftRight + turning;

  //   // double velArray[4] = {FLMotorVel, FRMotorVel, BLMotorVel, BRMotorVel};
  //   // internalVelocityControl(velArray, 1000);

  //   ForwardLeft.setVelocity(FLMotorVel, percent);
  //   ForwardRight.setVelocity(FRMotorVel, percent);
  //   BackLeft.setVelocity(BLMotorVel, percent);
  //   BackRight.setVelocity(BRMotorVel, percent);
  // }

  // void computeRelativeMotion(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer){
  //   const int deadband = 10;
  //   float theta = M_PI/180.0*(SensorSystem::getHeadingInertial());

  //   axis3 = abs(axis3) < deadband ? 0:axis3;
  //   axis4 = abs(axis4) < deadband ? 0:axis4;

  //   float upDown = -axis3*cos(theta) - axis4*sin(theta);
  //   float leftRight = -axis3*sin(theta) - axis4*cos(theta);

  //   combineDriveAndSpinMotionXDrive(upDown, leftRight, axis1, axis2, maxVelocityPer);
  // }

  
  void combineDriveAndSpinMotionStandardDrive(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer) {
    const int deadband = 10;
    const float turningRatio = axis4/100.0;
    const float turnSign = axis4 / abs(axis4);
    float upDown = (abs(axis3) < deadband) ? 0 : axis3;
    // parabolic
    // float turning = (abs(axis4) < deadband) ? 0 : turnSign * (turningRatio) * (turningRatio) * 100.0;
    // linear
    // float turning = (abs(axis4) < deadband) ? 0 : turningRatio * 100.0;
    // fourth power
    float turning = (abs(axis4) < deadband) ? 0 : turnSign * turningRatio * turningRatio * turningRatio * turningRatio * 100.0;

    // negatived values
    const double FRMotorVel = (upDown - turning);
    const double FLMotorVel = (upDown + turning);

    ForwardLeft.setVelocity(FLMotorVel, percent);
    // Geared Drive
    ForwardRight.setVelocity(FRMotorVel, percent);
    ForwardLeft.spin(forward);
    ForwardRight.spin(forward);
    //Chain Drive needs port 3
    //BackLeft.setVelocity(FRMotorVel, percent);
  }

  vex::timer turnTimer;
  PIDparameters *pidTurn = (new PIDparameters(" :) ", 15, 0.2, 0, 0))
                               ->setMinMax(0, 60)
                               ->setCooloffDelta(false, 100)
                               ->debug(false, true);
  vex::mutex isTurningToGoal;
}