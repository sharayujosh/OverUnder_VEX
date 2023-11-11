#pragma once

namespace Catapult{
  void retract();
  void release();

  void flipReloadCatapult(int nrTimes, float waitTimeMsec);
}