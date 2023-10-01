#pragma once
#include "Sensors.h"

//! Used to control the robot's drivetrain
namespace Drivetrain {
  /// @brief independent thread for controlling drivetrain
  int wheelLoop();  

  /// @brief correct heading for shifts between 360 degrees and 1 degree
  /// @param actualHeading inertial heading
  ///@param headingDifference difference between inertial heading and target heading
  float computeHeadingCorrectionVelocity(float actualHeading, float headingDifference);

  /// @brief stop voltages from being larger than max voltage
  /// @param maxVoltage
  /// @param voltages[4] pid adusted voltages for motors
  void normalizeMotorSettings(float maxVoltage, float voltages[4]);

  /// @brief prevent wheelLoop from executing 
  void lockWheelLoop();

  /// @brief allow wheelLoop to execute
  void unlockWheelLoop();

  /// @brief wait for wheelLoop to finish running
  void waitForDone();

  /// @brief track position of robot using odometry
  void updateOdometry();

  /// @brief get distance from number of gear rotations in motor
  float getDistanceFromTicks(float nrTicks);

  /// @brief turn until robot is centered on object
  /// @param Object name of field object
  /// @param headingInD inertial heading in degrees 
  /// @param timeInMS timeout in milliseconds
  //void turnToObject(Sensors::Color objColor, float headingInD, float extraOffset, float timeInMS, bool blocking = true);

  /// @brief turn at a constant velocity
  /// @param velocityInPer velocity in percent
  /// @param timeInMS timout in milliseconds
  void turnAtVelocity(float velocityInPer, float timeInMS, bool blocking = true);

  /*    ------------------    */
  /// @brief turn to an intertial heading
  /// @param headingInD inertial heading in degrees
  /// @param timeInMS timout in milliseconds
  void turnToHeading(float headingInD, float timeInMS, bool blocking = true);
  
  void turnToFieldPoint(float fieldX, float fieldY, float timeInMS, bool blocking);
  
  
  /*    ------------------    */
  /// @brief drive for a distance at an angle relative to the fixed field coordinate system
  /// @param DistanceInches distance in inches
  /// @param angleInD angle in degrees
  /// @param timeInMS timeout in milliseconds
  void driveForDistance (float DistanceInches, float angleInD, float timeInMS, bool blocking = true);

  void driveUntilDistSensor(float atVelocity, float minDist, float ignoreIfAboveMaxDist, float timeInMS, bool blocking);
  

  /*    ------------------    */
  /// @brief drive to a fixed coordinate point on the field using the field coordinate system
  /// @param xInches x-coordinate in inches
  /// @param yInches y-coordinate in inches
  /// @param timeInMS timout in milliseconds
  void driveToPosition (float xInches, float yInches, float timeInMS, bool blocking = true);
  /*    ------------------    */

  /// @brief drive forward relative to the robot coordinate system for a certain time at a certain velocity
  /// @param velocityInPer velocity in percent
  /// @param timeInMS timout in milliseconds
  void driveForTime(float velocityInPer, float timeInMS, bool blocking = true);

  void driveAtVelocity(float velocityInPer, float timeInMS, bool blocking = true);

  /// @brief drive forward relative to the robot coordinate system while centered on an object
  /// @param Object name of field object
  /// @param distanceInches distance in inches
  /// @param timeInMS timout in milliseconds
  //void driveCenteredOnObj(Sensors::Object fieldObject, float distanceInches, float timeInMS, bool blocking = true);
  
  void driveForTimeCenterDisc(float velocityInPercent, float timeInMS, bool blocking = true);
  
  void driveToGPS(float xPos, float yPos, float angle, float timeInMS, bool blocking = true);
  
  void driveForInches(float forwardDist, float lateralDist, float timeInMsec);
  void driveForInches(float forwardDist, float timeInMsec);

  /// @brief stop drivetrain motors
  void stop();

  /// @brief start drivetrain motors at zero velocity
  void start(); 

  void startWheelLoop();
  void stopWheelLoop();

  void setVelocity(float velocityInPercent); 
}