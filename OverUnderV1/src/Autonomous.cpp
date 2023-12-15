#include "Drivetrain.h"
#include "Catapult.h"
#include "math.h"
#include "Pid.h"
#include "Sensors.h"
#include "Settings.h"
#include "vex.h"

namespace Autonomous{
  void scoringAuton(){
    Catapult::retract();
    Claw.setStopping(hold);
    Claw.spinFor(reverse, 200, degrees, false);
    wait(500, msec);
    Drivetrain::driveForInches(44, 50000);
    wait(500, msec);
    Claw.spinFor(forward, 200, degrees, false);
    Drivetrain::driveForInches(-39, 50000);
    // Drivetrain::turnToHeading(245, 20000);
    // Catapult::halfRelease();
    // Drivetrain::driveForInches(52, 50000);
  }

  void descoreAuton(){
    Catapult::release();
    Drivetrain::turnToHeading(42, 20000);
    Drivetrain::driveForInches(-7, 50000);
    BackArm.spinFor(forward, 1000, degrees, false);
    wait(3000, msec);
    Drivetrain::turnToHeading(-10, 20000);
    //wait(2000, msec);
    BackArm.stop();
    BackArm.spinFor(forward, -1000, degrees, false);
    Drivetrain::turnToHeading(-40, 500);
    BackArm.spinFor(reverse, 190, degrees);
    Drivetrain::turnToHeading(45, 20000);
    Drivetrain::driveForInches(13, 50000);
    Drivetrain::turnToHeading(0, 20000);
    Drivetrain::driveForInches(40, 50000);
  }

  void autoSkills(){
    Catapult::retract();
    Drivetrain::turnToHeading(45, 20000);
    Drivetrain::driveForInches(12, 50000);
    Drivetrain::turnToHeading(-25, 20000);
    Drivetrain::driveForInches(6, 50000);
    Drivetrain::turnToHeading(-25, 20000);

    vex::wait(800, msec);
    // 15
    Catapult::flipReloadCatapult(20, 250);

    Drivetrain::driveForInches(-6, 50000);
    Drivetrain::turnToHeading(45, 20000);
    Drivetrain::driveForInches(-15, 50000);
    Drivetrain::turnToHeading(8, 20000);
    Drivetrain::driveForInches(-55, 50000);
    
    Drivetrain::turnToHeading(0, 20000);

    Drivetrain::driveForInches(-45, 50000);
    Drivetrain::turnToHeading(55, 20000);
    Drivetrain::driveForInches(67, 50000);
    Drivetrain::turnToHeading(175, 20000);

    Drivetrain::driveForInches(40, 50000);

    // Drivetrain::turnToHeading(225, 20000);
    // Drivetrain::driveForInches(-40, 50000);
    // Drivetrain::turnToHeading(180, 20000);
    // Drivetrain::driveForInches(40, 50000);

    // Drivetrain::turnToHeading(310, 20000);
    // Drivetrain::driveForInches(-60, 50000);
    // Drivetrain::turnToHeading(0, 20000);
    // Drivetrain::driveForInches(-80, 50000);
    // Drivetrain::turnToHeading(0, 20000);

    // Drivetrain::driveForInches(-36, 50000);
    // Drivetrain::driveForInches(7, 50000);
    // Drivetrain::turnToHeading(0, 20000);
    // Drivetrain::driveForInches(33, 50000);
    // Drivetrain::turnToHeading(-90, 20000);
    // Drivetrain::driveForInches(-20, 50000);

    // Drivetrain::turnToHeading(0, 20000);
    // Drivetrain::driveForInches(-36, 50000);
    // Drivetrain::driveForInches(40, 50000);
    // Drivetrain::turnToHeading(-90, 20000);
    // Drivetrain::driveForInches(-15, 50000);

    // Drivetrain::turnToHeading(0, 20000);
    // Drivetrain::driveForInches(-40, 50000);
    // Drivetrain::driveForInches(40, 50000);
  }
}