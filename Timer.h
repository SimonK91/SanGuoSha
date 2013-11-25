#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer
{
 private:
  int startTicks;
  bool started;
 public:
  Timer();
  ~Timer();
  void start();
  void stop();
  bool isStarted();
  int getTicks();
};
#endif
