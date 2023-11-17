#pragma once

//! Program settings
namespace Settings
{
  enum ALLIANCE_TYPE 
  {
    BLUE,
    RED
  };

  enum SKILLS_TYPE 
  {
    ON,
    OFF
  };

  ///@brief type of autonomous program should run
  enum RUN_TYPE
  {
    COMPETITION,       ///< competition setting
    TEST,              ///< testing setting
  };

  ///@brief type of drivetrain robot is using
  enum DRIVETRAIN_TYPE
  {
    XDRIVE,         ///< xdrive setting
    STANDARD_DRIVE, ///< standard drive setting
  };


  ///@brief type of test being run
  enum TEST_TYPE
  {
    DRIVE_FORWARD,
    DRIVE_FOR_TIME,
    DRIVE_MIX,
    DRIVE_GPS,
    DRIVE_TO_SENSOR,
    DRIVE_CENTER_DISC,
    RUN_FLY_WHEEL,
    RUN_INTAKE,
    TURN_TO_HEADING,
    TURN_TO_FIELD_POINT,
    TURN_AT_VELOCITY,
    PID,
    SHOOTER,
    TURN_INTAKE_TO_COLOR,
    CENTER_ON_GOAL,
    SHOOTER_RPM
  };

  enum AUTO_MATCH_TYPE
  {
    NONE,
    AUTO_SKILLS,
    DESCORE,
    SCORE,
    DRIVER_SKILLS
  };

  extern ALLIANCE_TYPE alliance;
  extern SKILLS_TYPE skills;
   
  const RUN_TYPE runType = COMPETITION;                  ///< current setting for type of run
  //const RUN_TYPE runType = TEST;                         ///< run tests
 
  const DRIVETRAIN_TYPE drivetrainType = STANDARD_DRIVE; ///< current setting for type of drivetrain
  const TEST_TYPE testType = DRIVE_CENTER_DISC;

  extern AUTO_MATCH_TYPE autoMatchType; // = DESCORE;
  //const AUTO_MATCH_TYPE autoMatchType = ROLLER_GOAL_SIDE;
  //const AUTO_MATCH_TYPE autoMatchType = ROLLER_GOAL;
  //const AUTO_MATCH_TYPE autoMatchType = AUTO_SKILLS;

}