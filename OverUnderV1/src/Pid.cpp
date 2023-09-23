#include "Pid.h"
//#include "Log.h"
#include "math.h"

namespace Pid{
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
}


