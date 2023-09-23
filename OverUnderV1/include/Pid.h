#pragma once
#include <string>

//! Controls PID parameters and output
struct PIDparameters
{
  float target; /// < target value
  float actual; /// < current value (will eventually become target value)

  float kStart; /// < constant of proportionality for beginning of action
  float Kp;     /// < constant of proportionality for the remainder of action
  float Kd;     /// < constant of proportionality for derivative
  float Ki;     /// < constant of proportionality for integral

  std::string label; /// < string of labels for printing

  float maxOut; /// < maximum power output
  float minOut; /// < minimum power output

  float error;  /// < difference  between target value and current value
  float dError; /// < difference between current error reading and the previous error reading

  float prevMeasurement; /// < previous actual (old "current value")
  float prevError;       /// < previos error

  float dMeasurement; /// < difference between current actual value and previous actual value
  float dCutoff;      /// < lower cutoff for derivative

  bool allowCooloffs; /// < switch on and off cooloffs
  int coolDownCycles; /// < number of cycles robot cools off for

  float integral;                      /// < sum of errors
  float integralErrorCutoff = 1000000; /// < lower cutoff for integral

  /// @brief contructor for PID parameter
  /// @param std::string label string of labels for printing
  /// @param kStart constant of proportionality for beginning of action
  /// @param Kp constant of proportionality for the remainder of action
  /// @param Kd constant of proportionality for derivative, if not specified set to zero
  /// @param Ki constant of proportionality for integral, if not specified set to zero
  PIDparameters(std::string label, float kStart, float Kp, float Kd = 0, float Ki = 0)
      : kStart(kStart), Kp(Kp), Kd(Kd), Ki(Ki)
  {
    integral = 0;
    dError = 0;
    dMeasurement = 0;
    coolDownCycles = 0;
    prevError = 0;
    minOut = 10;
    maxOut = 10000;
    allowCooloffs = false;
  }

  PIDparameters *debug(bool printEachIteration, bool recordBehavior)
  {
    return this;
  }

  /// @brief set cooloff settings
  /// @param allowCooloffs switch cooloffs on or off
  /// @param set lower cutoff for derivative
  /// @return pointer to self
  PIDparameters *setCooloffDelta(bool allowCooloffs, float dCutoff)
  {
    this->allowCooloffs = allowCooloffs;
    this->dCutoff = dCutoff;
    return this;
  }

  /// @brief set power output min and max
  /// @param minOut minimum power output
  /// @param maxOut maximum power output
  /// @return pointer to self
  PIDparameters *setMinMax(float minOut, float maxOut)
  {
    this->maxOut = maxOut;
    this->minOut = minOut;
    return this;
  }

  /// @brief get power output for motors given target value and actual value
  /// @param target target value
  /// @param actual current value
  /// @param timeElapsedMsec time that has gone by since beginning of action
  float getPowerOutput(float target, float actual, float timeElapsedMsec);

  float getMotorOutput(float targetValue, float actualValue, float timeElapsed, float maxOut, float minOut, float kStart, float kEnd);

  /// @brief reset integral and derivatives back to zero
  void reset();

  /// @brief print variables of the PID struct and their values to the terminal while in debugging mode
  void printParameters();
  void printBehavior();
};