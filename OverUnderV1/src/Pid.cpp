#include "Pid.h"
//#include "Log.h"
#include "math.h"

float PIDparameters::getPowerOutput(float target, float actual, float timeElapsedMsec)
{
  if (timeElapsedMsec < 0.00001)
  {
    return 0;
  }
  this->target = target;
  this->actual = actual;

  float tmpError = target - actual;

  this->dError = this->error - tmpError;
  this->error = tmpError;

  float tmpDMeasurement = actual - this->prevMeasurement;
  this->prevMeasurement = actual;

  // if large changes in readings occurs, set cooloff
  if (this->allowCooloffs && (fabs(tmpDMeasurement) > dCutoff or prevError * dError < -1))
  {
    this->dMeasurement = 0;
    this->coolDownCycles = 1;
  }

  prevError = dError;

  float tmpIntegral = this->integral + tmpError;
  if (fabs(this->Ki * tmpIntegral) < this->integralErrorCutoff)
  {
    this->integral = tmpIntegral;
  }

  // starting values should follow startLine, ending values endLine
  float startLine = this->kStart * timeElapsedMsec * 0.001;
  float endLine = this->Kp * this->error + this->Kd * this->dError + this->Ki * this->integral;

  float sign = fabs(endLine) / endLine;

  float motorOutput = fmin(fabs(startLine), maxOut);

  motorOutput = fmin(motorOutput, fabs(endLine));
  motorOutput = fmax(motorOutput, minOut);

  if (this->coolDownCycles > 0)
  {
    this->coolDownCycles--;
    motorOutput = minOut;
  }

  return motorOutput * sign;
}

void PIDparameters::reset()
{
  this->integral = 0;
  this->dError = 0;
}

// void PIDparameters::printParameters()
// {
//   Log::debug("%s PID Parameters: ", label.c_str());
//   Log::debug("Kstart=%4.2f, ", this->Kp);
//   Log::debug("Kp=%4.2f, ", this->Kd);
//   Log::debug("Kd=%4.2f, ", this->Kp);
//   Log::debug("Ki=%4.2f, ", this->Ki);
//   Log::debug("OutputRange=(%4.1f, %4.1f)\n", this->minOut, this->maxOut);
// }
