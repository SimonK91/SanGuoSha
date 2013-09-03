#include "object_window.h"


void window::makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string command)
{
  objects.push_back(new button(text, xPos, yPos, command));
} 

void window::handleEvents(SDL_Event event, pointer_arrow arrow )
{
  
  for(auto i: objects)
    {
      if(static_cast<active_object*>(*i) != nullptr)
	{
	  static_cast<active_object>(*i)->handleEvent(event, arrow);
	}
    }
  
}

void window::print(SDL_Surface* screen)
{
  
}
