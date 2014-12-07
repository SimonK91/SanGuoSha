#ifndef SLIDER_H
#define SLIDER_H

#include "Objects.h"
#include <string>
 
namespace Object
{
  class Slider : public ActiveObject
  {
  private:
    Surface bg;
    Surface btn;
    SDL_Rect btn_box;
    int offset;
    int box_min;
    int box_max;
    
  public:
    Slider(const int& x, const int& y, const std::string& command, const int& val,
	   const std::string& bg_i = "Images/Gui/thickSlider.png", const int& edge = 20,
	   const std::string& btn_i = "Images/Gui/thickSliderButton.png");
    ~Slider();
    
    bool inside( const SDL_Event& event);   
    std::string handleEvent(const SDL_Event&);    
    void paint(Surface& to_where);        	
  };
}//slut på namespace
#endif
