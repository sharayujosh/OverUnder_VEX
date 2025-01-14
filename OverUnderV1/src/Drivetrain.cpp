#include "Drivetrain.h"
#include "math.h"
#include "vex.h"
#include "Pid.h"

namespace Drivetrain {
  static const float wheelRadiusInches = 2.0;

  float getNrRotations(float dist, float wheelRadiusIn){
    return (dist/(wheelRadiusIn*2*M_PI));
  }

  float getMotorOutput(float targetValue, float actualValue, float timeElapsed, float maxOut, float minOut, float kStart, float kEnd){
    float startLine = kStart*timeElapsed;
    float endLine = kEnd * (targetValue - actualValue);
    float minLine = minOut;
    float maxLine = maxOut;
    float motorOutput = fmin(startLine, maxLine);
    motorOutput = fmin(motorOutput, endLine);
    motorOutput = fmax(motorOutput, minLine);

    return motorOutput;
  }

  void driveForInches(float forwardDist, float lateralDist, float timeout){
    vex::timer motorTimer;
    motorTimer.reset();
    float dx = forwardDist*cos(M_PI / 4) - lateralDist*cos(M_PI / 4);
    float dy = forwardDist*sin(M_PI / 4) - lateralDist*sin(M_PI / 4);
    float targetRotationX = getNrRotations(dx, wheelRadiusInches);
    float targetRotationY = getNrRotations(dy, wheelRadiusInches);
    ForwardLeft.resetRotation();
    ForwardRight.resetRotation();
    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);
    ForwardLeft.spin(forward);
    ForwardRight.spin(forward);
    float differenceX = targetRotationX;
    float differenceY = targetRotationY;
    float smallValue = -1;
    float counter = 1;
    int sleepTime = 20;
    while((fabs(differenceX) > smallValue or fabs(differenceY) > smallValue) and motorTimer.time() < timeout){
      float actualRotationX = ForwardRight.rotation(turns);
      float actualRotationY = ForwardLeft.rotation(turns);
      float velocityX = getMotorOutput(targetRotationX, actualRotationX, sleepTime*counter, 100, 10, 5, 5);
      float velocityY = getMotorOutput(targetRotationY, actualRotationY, sleepTime*counter, 100, 10, 5, 5);
      ForwardRight.setVelocity(velocityX, percent);
      ForwardLeft.setVelocity(velocityY, percent);
      differenceX = targetRotationX - actualRotationX;
      differenceY = targetRotationY - actualRotationY;
      vex::task::sleep(sleepTime);
      counter++;
    }
    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);
  }

  void driveForInches(float forwardDist, float timeout){
    vex::timer motorTimer;
    motorTimer.reset();

    float targetRotation = getNrRotations(forwardDist, wheelRadiusInches);
    printf("Target Rotation: %f\n", targetRotation);

    ForwardRight.resetRotation();

    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);

    ForwardLeft.spin(forward);
    ForwardRight.spin(forward);

    float difference = targetRotation;

    float deadband = 0.01;
    float counter = 1;
    int sleepTime = 20;

    while(fabs(difference) > deadband and motorTimer.time() < timeout){
      float actualRotation = ForwardRight.rotation(turns);
      float velocity = (forwardDist/fabs(forwardDist)) * getMotorOutput(fabs(difference), 0, 
                sleepTime*counter, 100, 10, 80, 80);

      ForwardRight.setVelocity(velocity, percent);
      ForwardLeft.setVelocity(velocity, percent);

      difference = targetRotation - actualRotation;
      vex::task::sleep(sleepTime);
      counter++;
      printf("difference: %f\n", difference);
    }
    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);
  }

  void turnToHeading(float headingInD, float timeInMS){
    vex::timer motorTimer;
    motorTimer.reset();

    float targetHeading = headingInD;
    float currentHeading = Inertial.heading();

    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);

    ForwardLeft.spin(forward);
    ForwardRight.spin(reverse);

    float difference = (currentHeading - targetHeading);

    if (fabs(difference) > 180)
    {
      difference = (fabs(difference) - 360) *
                    fabs(difference) / difference;
    }


    float deadband = 1;
    float counter = 1;
    int sleepTime = 20;

    while(fabs(difference) > deadband and motorTimer.time() < timeInMS){
      currentHeading = Inertial.heading();
      float velocity = fabs(difference)/difference*getMotorOutput(fabs(difference), 0, 
                sleepTime*counter, 70, 10, 0.50, 0.50);

      ForwardRight.setVelocity(velocity, percent);
      ForwardLeft.setVelocity(-velocity, percent);

      difference = (currentHeading - targetHeading);

      if (fabs(difference) > 180)
      {
        difference = (fabs(difference) - 360) *
                       fabs(difference) / difference;
      }

      vex::task::sleep(sleepTime);
      counter++;
      printf("difference: %f\n", difference);
    }
    ForwardRight.setVelocity(0, percent);
    ForwardLeft.setVelocity(0, percent);
  }
}