#include "FrameRateFixer.h"
#include "SDL/SDL.h"

FrameRateFixer::FrameRateFixer()
{
    //Initialize the variables
    startTicks = 0;
	FPS = 60;
	frameDelay = 1000 / FPS;
}

void FrameRateFixer::start()
{
    startTicks = SDL_GetTicks();
	frames = 0;
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

void FrameRateFixer::setFPS(int framesPerSecond)
{
	FPS = framesPerSecond;
}

long FrameRateFixer::get_ticks()
{
    //Return the current time minus the start time
    return SDL_GetTicks() - startTicks;
}
