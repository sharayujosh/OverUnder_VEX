#pragma once

namespace Catapult{
  void retract();
  void release();
  void halfRelease();

  void flipReloadCatapult(int nrTimes, float waitTimeMsec);
}