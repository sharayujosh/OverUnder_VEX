#include "Flap.h"
#include "vex.h"

namespace Flap{
  void release(){
  DigitalOutB.set(false);
  DigitalOutC.set(false);
  }

  void engage(){
  DigitalOutB.set(true);
  DigitalOutC.set(true);
  }
}
