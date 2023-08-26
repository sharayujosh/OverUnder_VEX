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
    //Chain Drive needs port 3
    //BackLeft.setVelocity(FRMotorVel, percent);
  }

  vex::timer turnTimer;
  PIDparameters *pidTurn = (new PIDparameters(" :) ", 15, 0.2, 0, 0))
                               ->setMinMax(0, 60)
                               ->setCooloffDelta(false, 100)
                               ->debug(false, true);
  vex::mutex isTurningToGoal;

  // void turnToGoal(){
  //    //Log::debug("Drive control: Turn to Goal\n");
  //    isTurningToGoal.lock();
  //    turnTimer.reset();
  //    const int cameraWidthX = 316;
  //    const int cameraOffset = 20; // bigger turns robot left
  //    const int timeout = 1500;
  //    int noObjFoundCounter = 0;

  //    if (!ShooterSystem::isSpinning){
  //       //Log::debug("heyyyyy I'm shooting now");
  //       ShooterSystem::start();
  //       ShooterSystem::setVelocity(1950);
  //    }
    
  //      SensorSystem::Color aimAt = SensorSystem::Color::RED;
  //     if (Settings::skills == Settings::SKILLS_TYPE::OFF){
  //       aimAt = Settings::alliance == Settings::ALLIANCE_TYPE::RED ? SensorSystem::Color::RED : SensorSystem::Color::BLUE;
  //     } else if (45 > SensorSystem::getHeadingInertial() || SensorSystem::getHeadingInertial() > 225) {
  //       aimAt = Settings::alliance == Settings::ALLIANCE_TYPE::RED ? SensorSystem::Color::RED : SensorSystem::Color::BLUE;
  //     } else {
  //       aimAt = Settings::alliance == Settings::ALLIANCE_TYPE::RED ? SensorSystem::Color::BLUE : SensorSystem::Color::RED;
  //     }

  //   while (noObjFoundCounter < 5 && turnTimer.time() < timeout) {
  //     Log::debug(" Turn to Goal Cycle\n");
  //     SensorSystem::VisionInfo objectInfo = SensorSystem::findColor(aimAt);

  //     float headingDifference = 0;
      
  //     if (objectInfo.quality > 0) {
  //       float xPos = objectInfo.xPix;
  //       float yPos = objectInfo.yPix;
  //       float width = objectInfo.width;
  //       float height = objectInfo.height;

  //       // check shape and location (avoid other red / blue objects)
  //       if (yPos > 65 && yPos < 130 &&
  //           width > 35 && width < 110 &&
  //           height > 10 && height < 60){
  //         noObjFoundCounter = 0;
  //         // distance 
  //         // 125 = 80 inch
  //         // 69 = 38 inch

  //         Log::debug("yPos: %f \n", yPos);

  //         if(0 < yPos && yPos <= 105) {
  //           ShooterSystem::setVelocity(1800);
  //           Log::debug("0 to 105 \n");
  //         } else if (105 < yPos && yPos <= 125) {
  //           ShooterSystem::setVelocity(2100);
  //           Log::debug("105 to 125 \n");
  //         } else if (125 < yPos) {
  //           ShooterSystem::setVelocity(2300);
  //           Log::debug("125 to infinity \n");
  //         }


  //         headingDifference = (xPos - cameraWidthX/2.0 - cameraOffset);
  //         Log::debug("headingDiff: %3.1f, (%3.1f)\n", headingDifference, xPos);
  //         if (fabs(headingDifference) < 3)
  //         {
  //           // set range
  //           //ShooterSystem::setVelocity(1750); 
  //           ForwardLeft.setVelocity(0, percent);
  //           ForwardRight.setVelocity(0, percent);
            
  //           isTurningToGoal.unlock();
  //           return;
  //         }

  //         float velPer = pidTurn->getPowerOutput(0, headingDifference, turnTimer.time());
  //         ForwardLeft.setVelocity(-velPer, percent);
  //         ForwardRight.setVelocity(velPer, percent);
        
         
  //       }
  //     } else {
  //       noObjFoundCounter ++;
  //     }

  //     vex::wait(20, msec);
  //   }
  
  //   Log::debug(" Turn to Goal Cycle Failed\n");
    
  //   // failed to find goal
  //   Controller1.rumble("----");
    
  //   ForwardLeft.setVelocity(0, percent);
  //   ForwardRight.setVelocity(0, percent);
    
  //   isTurningToGoal.unlock();
  // }
}