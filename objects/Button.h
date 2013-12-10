#ifndef BUTTON_H
#define BUTTON_H

#include "Objects.h"
#include "../functions.h"
#include <string>

namespace Object
{
  
  class Button : public ActiveObject
  {
  private:
    std::vector<SDL_Rect> clip;
    Surface button_sheet;
    
  public:
    Button(const std::string& name, int x, int y, const std::string& command,
	   const std::string& image, const unsigned& size);
    
    ~Button() = default;
    
    bool inside( const SDL_Event&);
    std::string handleEvent( const SDL_Event&);
    
    void paint(Surface&);
  };
  
}//slut på namnrymden
#endif
