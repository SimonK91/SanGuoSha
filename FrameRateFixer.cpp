#include "FrameRateFixer.h"
#include "SDL/SDL.h"
#include <iostream>

FrameRateFixer::FrameRateFixer(unsigned fps) : FPS(fps) {}

void FrameRateFixer::start()
{
  startTicks = SDL_GetTicks();
  lastTick = get_ticks();
  frameDelay = 1000/FPS;
}

void FrameRateFixer::regulateFPS()
{
  
  if(get_ticks() < frameDelay) 
    {
      //Sleep the remaining frame time
      SDL_Delay( frameDelay - get_ticks() );
    }
  frameDelay += 1000 / FPS;
}

void FrameRateFixer::setFPS(unsigned framesPerSecond)
{
  FPS = framesPerSecond;
}

unsigned FrameRateFixer::get_ticks()
{
  return SDL_GetTicks() - startTicks;
}

//first frametime is bonkers but rest is okay
unsigned FrameRateFixer::getFrameTime()
{
  unsigned frameTime = get_ticks() - lastTick;
  lastTick = get_ticks();
  
  return frameTime;
}
