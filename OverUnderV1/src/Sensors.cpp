#include "Sensors.h"
#include "vex.h"
//#include "Log.h"
#include "Accumulator.h"

namespace SensorSystem
{
  Accumulator xGPSmm(3);
  Accumulator yGPSmm(3);
  Accumulator headingGPS(3);
  Accumulator heading(2);

  vex::mutex sensorMutex; 
  vex::mutex cameraMutex;

  int sensorLoop(){
    while (true)
    {
      sensorMutex.lock();
      // float quality = GPS15.quality();

      // if (quality > 95){
      //   xGPSmm.set(GPS15.xPosition(mm));
      //   yGPSmm.set(GPS15.yPosition(mm));
      //   headingGPS.setWithAngle(GPS15.heading(degrees));
      // }
      
      heading.setWithAngle(Inertial.heading(degrees));

      sensorMutex.unlock();
      wait(50, msec);
    }
    return 0;
  }

  void setDirection(float angle){
    Inertial.setHeading(angle, degrees);
  }

  /// returns robot heading according to inertial sensor in degrees
  float getHeadingInertial()
  {
    //Log::debug("\n1: %f, 2: %f", Inertial.heading(degrees), Inertial2.heading(degrees));
    return (Inertial.heading(degrees));//+ Inertial2.heading(degrees))/2;
  }

  // /// returns the distance to the object detected in inches
  // float getDistanceToObject()
  // {
  //   return Distance.objectDistance(inches);
  // }

  // /// returns whether or not the bumper is pressed
  // bool isBumperPressed()
  // {
  //   return Bumper.pressing();
  // }

  // /// returns whether or not the optical sensor detects an object
  // bool isDiscDetected()
  // {
  //   return Optical.isNearObject();
  // }

  // /// returns whether or not a jumper in in A
  // bool isXDrive()
  // {
  //   return DigitalInA.value();
  // }

  // bool limitIsPressed()
  // {
  //   return false;
  // }

  // signature getObjectSignature(Object objectToGet)
  // {
  //   signature sig;
  //   // switch(objectToGet){
  //   //   case RED_HIGHGOAL:

  //   // }
  //   return sig;
  // }

  // /// returns a vector to a detected object
  // std::vector<VisionInfo> findObject(Object objectToFind)
  // {
  //   std::vector<VisionInfo> objectVector; 
  //   // Vision.takeSnapshot(Object); ///no Objects in SensorSystem.h have been written yet
  //   // VisionInfo *visionInfo = new VisionInfo();
  //   // visionInfo->xPix = Vision.objects[0].centerX;
  //   // visionInfo->yPix = Vision.objects[0].centerY;
  //   // visionInfo->width = Vision.objects[0].width;
  //   // visionInfo->height = Vision.objects[0].height;
  //   // objectVector.push_back(*visionInfo);
  //   return objectVector;
  //   /// Figure out certainty
  // }


  // bool isElevatedGoal(SensorSystem::VisionInfo vi){
  //   // check shape and location (avoid other red / blue objects)
  //   if (vi.yPix > 65 && vi.yPix < 130 &&
  //       vi.width > 35 && vi.width < 110 &&
  //       vi.height > 10 && vi.height < 60){
  //       return true;
  //   }

  //   return false;
  // }

  // VisionInfo findDisc(){
  //   cameraMutex.lock();
  //   DiscVision.takeSnapshot(DiscVision__DV_YELLOW);
  //   int nrObjects = DiscVision.objectCount;
  //   VisionInfo visionInfo;

  //   if(nrObjects > 0){  
  //     visionInfo.xPix = DiscVision.largestObject.centerX;
  //     visionInfo.yPix = DiscVision.largestObject.centerY;
  //     visionInfo.width = DiscVision.largestObject.width;
  //     visionInfo.height = DiscVision.largestObject.height;
  //     visionInfo.quality = 100;
  //   }

  //   cameraMutex.unlock();
    
  //   return visionInfo;
  // }

  // VisionInfo findColor(Color objColor){
  //   cameraMutex.lock();

  //   switch (objColor){
  //     case RED:
  //       Vision.takeSnapshot(Vision__SIG_1);
  //       break;
  //     case BLUE:
  //     default:        
  //       Vision.takeSnapshot(Vision__SIG_2);
  //       break;
  //   }
    
  //   int nrObjects = Vision.objectCount;
  //   VisionInfo visionInfo;

  //   if(nrObjects > 0){  
  //     //VisionInfo *visionInfo = new VisionInfo();
  //     visionInfo.xPix = Vision.largestObject.centerX;
  //     visionInfo.yPix = Vision.largestObject.centerY;
  //     visionInfo.width = Vision.largestObject.width;
  //     visionInfo.height = Vision.largestObject.height;
  //     visionInfo.quality = 100;
  //     // objectVector.push_back(*visionInfo);
  //   }

  //   cameraMutex.unlock();
    
  //   return visionInfo;
  // }

  // float getVelocityShooterRotation()
  // {
  //   return ShooterRotation.velocity(rpm);
  // }

  // float getHeadingGPS(){
  //   return GPS15.orientation(pitch, deg);
  // }

  // float getXInchesGPS(){
  //   return GPS15.xPosition(inches);
  // }

  // float getYInchesGPS(){
  //   return GPS15.yPosition(inches);
  // }

  // float getGPSQuality() {
  //   return GPS15.quality();
  // }

  // float getXMMGPSAvg(){
  //   sensorMutex.lock();
  //   float avg = xGPSmm.getAverage();
  //   sensorMutex.unlock();
  //   return avg;
  // }

  // float getYMMGPSAvg(){
  //   sensorMutex.lock();
  //   float avg = yGPSmm.getAverage();
  //   sensorMutex.unlock();
  //   return avg;
  // }

  // float getGPSHeadingAvg(){
  //   sensorMutex.lock();
  //   float avg = headingGPS.getAverage();
  //   sensorMutex.unlock();
  //   return avg;
  // }

  float getHeadingAvg(){
    sensorMutex.lock();
    float avg = heading.getAverage();
    sensorMutex.unlock();
    return avg;
  }
}