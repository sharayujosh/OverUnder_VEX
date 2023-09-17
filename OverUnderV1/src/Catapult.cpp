#include "Catapult.h"
#include "vex.h"

namespace Catapult{

  void flipCatapult(){
    CatapultMotor.setVelocity(100, percent);
    CatapultMotor.spinFor(forward, 90, degrees);
  }

}