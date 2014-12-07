#include "Timer.h"


Timer::Timer(int x_pos, int y_pos, int sec, std::string com)
{
  start_ticks = 0;
  paused_ticks = 0;
  started = false;
  paused = false;
  seconds = sec;
  command = com;
  
  bar.setImage( loadImage("Images/Gui/loading-bar.png", true) );
  frame.setImage( loadImage("Images/Gui/loading-frame.png", true) );
  	
  pos.x = x_pos;
  pos.y = y_pos;
}

Timer::~Timer()
{
  
}

void Timer::start(int sec)
{
  started = true;
  paused = false;
  seconds = sec;
  start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
  started = false;
  paused = false;
}

void Timer::pause()
{ 
  if( (started) && (!paused) )
    {
      paused = true;
      paused_ticks = SDL_GetTicks() - start_ticks;
    }
}

void Timer::unPause()
{
  if(paused)
    {
      paused = false;     
      start_ticks = SDL_GetTicks() - paused_ticks;
      paused_ticks = 0;
    }  
}

int Timer::getTicks()
{
  if(started)
    {
      if(paused)
	{
	  return paused_ticks;
	}
      else
	{
	  return SDL_GetTicks() - start_ticks;
	}      
    }
  return 0;  
}

bool Timer::checkStarted()
{
  return started;
}

bool Timer::checkPaused()
{
  return paused;
}

void Timer::paint(Surface screen)
{
  SDL_Rect bar_clip;
  bar_clip.x = 0;
  bar_clip.y = 0;
  bar_clip.h = 35;
  
  int offset = bar->w / seconds;
  
  bar_clip.w = (getTicks()/1000.0) * offset ;
  
  applySurface(pos.x, pos.y, bar, screen, &bar_clip);
  applySurface(pos.x, pos.y, frame, screen);
}

void Timer::setPos(int x_pos, int y_pos)
{
  pos.x = x_pos;
  pos.y = y_pos;
} 

std::string Timer::time_ran_out()
{
  if(checkStarted() == true)
    {
      if( (getTicks() / 1000) >= seconds )
	{
	  return command;
	}
    }
  return "";
}

void Timer::setCommand(std::string com)
{
  command = com;
}

void Timer::reset(int time, std::string cmd)
{
  if(checkStarted() == true)
    {
      stop();
    }
  start(time);
  setCommand(cmd);
}
