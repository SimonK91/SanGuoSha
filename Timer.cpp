#include "Timer.h"


Timer::Timer()
{
  startTicks = 0;
  started = false;
  
}

Timer::~Timer()
{
}

void Timer::start()
{
  started = true;
  startTicks = SDL_GetTicks();
}

void Timer::stop()
{
  started = false;
}

bool Timer::isStarted()
{
  return started;
}

int Timer::getTicks()
{
  if(started == true)
    {
      return SDL_GetTicks() - startTicks;
    }

  return 0;
}
