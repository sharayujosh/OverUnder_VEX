
#include "Accumulator.h"

Accumulator::Accumulator(int maxNrValues){
  nextLocation = 0;
  values = new float[maxNrValues];
  this->maxNrValues = maxNrValues;
}

void Accumulator::setWithAngle(float value){
  float diff = initialize ? getAverage() - value : 0;

  if (initialize == false || (diff < 300 || diff > 300)){
    for (int i = 0; i < maxNrValues; i++){
      values[i] = value;
    }
    initialize = true;
  }

  values[nextLocation] = value;

  nextLocation++;
  if (nextLocation >= maxNrValues){
    nextLocation = 0;
  }
}

void Accumulator::set(float value){
  if (initialize == false){
    for (int i = 0; i < maxNrValues; i++){
      values[i] = value;
    }
    initialize = true;
  }
  values[nextLocation] = value;
  nextLocation++;
  if (nextLocation >= maxNrValues){
    nextLocation = 0;
  }
}

float Accumulator::getAverage(){
  float sum = 0;
  for (int i = 0; i < maxNrValues; i++){
    sum = sum + values[i];
  }
  float average = sum / maxNrValues;
  return average;
}