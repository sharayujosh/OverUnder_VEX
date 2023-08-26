#pragma once

class Accumulator{
  public:
    int maxNrValues;          /// < maximum number of values that can be in the accumulator
    int nextLocation;         /// < next place to put a value
    float *values;            /// < values in the accumulator
    bool initialize = false;  /// < accumulator running

    /// @brief constructor (creates accumulator)
    /// @param maximum number of values
    Accumulator(int maxNrValues);

    /// @brief tells accumulator to start creating values
    /// @param float value
    void set(float value);
    
    /// @brief accounting for properties of angles
    /// @param float value
    void setWithAngle(float value);

    /// @brief takes average of values
    float getAverage();
};