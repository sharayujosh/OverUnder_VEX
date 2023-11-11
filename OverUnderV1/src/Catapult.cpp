#include "Catapult.h"
#include "vex.h"

namespace Catapult{

  void retract(){
  CatapultMotor.setStopping(hold);
  CatapultMotor.setVelocity(90, percent);
  CatapultMotor.spin(forward);

  while(!LimitSwitchC.pressing()){
    wait(10, msec);
  }

  CatapultMotor.stop();
  }
  void release(){
    CatapultMotor.setStopping(coast);
    CatapultMotor.setVelocity(30, percent);
    CatapultMotor.spin(forward);
    wait(300, msec);
    //CatapultMotor.stop();

    CatapultMotor.setStopping(hold);
    CatapultMotor.setVelocity(90, percent);
    CatapultMotor.spin(forward);

    while(!LimitSwitchC.pressing()){
      wait(10, msec);
    }

    CatapultMotor.stop();
  }

  void flipReloadCatapult(int nrTimes, float waitTimeMsec){
   for (int i = 0; i < nrTimes; i++){
     release();
     vex::wait(waitTimeMsec, msec);
   }
  }

}