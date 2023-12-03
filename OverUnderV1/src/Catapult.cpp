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
    CatapultMotor.setVelocity(100, percent); // 30
    CatapultMotor.spin(forward);
    wait(250, msec);
    //CatapultMotor.stop();

    CatapultMotor.setStopping(hold);
    CatapultMotor.setVelocity(100, percent); // 90
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