#pragma once
#include <vector>

//! Used to interface with the sensors on the robot
namespace Sensors
{
  enum Color
  {
    BLUE,   ///< color blue
    RED,    ///< color red
    YELLOW, ///< color yellow
    WHITE   ///< color white
  };

  enum Object
  {
    RED_HIGHGOAL,  ///< red alliance high goal
    BLUE_HIGHGOAL, ///< blue alliance high goal
    RED_LOWGOAL,   ///< red alliance low goal
    BLUE_LOWGOAL,  ///< blue alliance low goal
    DISC,          ///< a disc
    ROLLER,        ///< a roller
    LINE           ///< the field divison line
  };

  /// @struct VisionInfo
  /// @brief all information associated with identifying the image location of a field object
  /// @var VisionInfo::xPix
  /// Member 'xInches' contains x coordinate
  /// @var VisionInfo::yPix
  /// Member 'yInches' contains y coordinate
  /// @var VisionInfo::quality
  /// Members 'quality' contains certainty that object has been identified
  struct VisionInfo
  {
    float xPix = 0;
    float yPix = 0;
    float width = -1;
    float height = -1;
    float quality = 0;
  };

  int sensorLoop();

  // float getXMMGPSAvg();
  // float getYMMGPSAvg();
  // float getGPSHeadingAvg();
  float getHeadingAvg();


  /// @brief get inertial heading
  /// @return value in degrees
  float getHeadingInertial();

  // /// @brief get GPS heading
  // /// @return value in degrees
  // float getHeadingGPS();

  // /// @brief get GPS X coordinate
  // /// @return value in inches
  // float getXInchesGPS();

  // /// @brief get GPS Y coordinate
  // /// @return value in inches
  // float getYInchesGPS();

  // /// @brief get GPS quality
  // /// @return value in percent
  // float getGPSQuality();

  // /// @brief get X and Y coordinates of objects and certainty that object has been identified
  // /// @param Object field object
  // /// @return vector of visionInfo for found field objects
  // std::vector<VisionInfo> findObject(Object obj);

  // VisionInfo findColor(Color objColor);
  // VisionInfo findDisc();
  
  // bool isElevatedGoal(SensorSystem::VisionInfo vi);
  

  // /// @brief is limit switch pressed
  // bool limitIsPressed(); 

  // /// @brief get distance to object from distance sensor
  // float getDistanceToObject();

  // /// @brief get velocity of shooter from rotation sensor
  // /// @return value in percent
  // float getVelocityShooterRotation();
}