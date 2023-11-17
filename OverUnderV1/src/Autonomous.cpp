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
    Claw.spinFor(reverse, 200, degrees);
    Drivetrain::driveForInches(44, 50000);
    Claw.spinFor(forward, 200, degrees);
    Drivetrain::driveForInches(-35, 50000);
    Drivetrain::turnToHeading(300, 20000);
    Catapult::release();
    Drivetrain::driveForInches(-52, 50000);
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
    Drivetrain::turnToHeading(-29, 20000);
    Drivetrain::driveForInches(6, 50000);
    Drivetrain::turnToHeading(-29, 20000);

    vex::wait(800, msec);

    Catapult::flipReloadCatapult(15, 300);

    Drivetrain::turnToHeading(310, 20000);
    Drivetrain::driveForInches(-65, 50000);
    Drivetrain::turnToHeading(0, 20000);
    Drivetrain::driveForInches(-76, 50000);
    Drivetrain::turnToHeading(0, 20000);

    Drivetrain::driveForInches(-36, 50000);
    Drivetrain::driveForInches(7, 50000);
    Drivetrain::turnToHeading(0, 20000);
    Drivetrain::driveForInches(33, 50000);
    Drivetrain::turnToHeading(-90, 20000);
    Drivetrain::driveForInches(-20, 50000);

    Drivetrain::turnToHeading(0, 20000);
    Drivetrain::driveForInches(-36, 50000);
    Drivetrain::driveForInches(40, 50000);
    Drivetrain::turnToHeading(-90, 20000);
    Drivetrain::driveForInches(-15, 50000);

    Drivetrain::turnToHeading(0, 20000);
    Drivetrain::driveForInches(-40, 50000);
    Drivetrain::driveForInches(40, 50000);
  }
}