#include "object_window.h"

namespace object
{
  void window::makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string command)
  {
    button* tmp = new button(text, xPos, yPos, command);
    objects.push_back(tmp);
  } 
  
  window::~window()
  {
    clean_up( {background,topBorder,bottomBorder,leftBorder,rightBorder,bottomRightCorner,bottomLeftCorner,topRightCorner, topLeftCorner},{});
    
    for(auto i : objects)
      {
	delete i;
      }
  }  
  void window::makeTextBox(/*konstruktor argument för en textbox*/)
  {
    
    // textBox* tmp = new textBox();
    //objects.push_back(tmp);
    
  }
  
  void window::makeSlider()
  {
  }
  void window::makeCheckBox()
  {
  }
  std::string window::handle_event(const SDL_Event& event, const pointer_arrow& arrow )
  {
    std::string tmpCommand = "";
    for(auto i: objects)
      {
	if(dynamic_cast<active_object*>(i) != nullptr)
	  {
	    tmpCommand =  dynamic_cast<active_object*>(i)->handle_event(event, arrow);
	  }
      }
    
    return tmpCommand;
    
  }
  
  
  void window::print(SDL_Surface* screen)
  {
    //dessa SDL_Rects används för att se till att backgrunden och ramen "skalas om" till rätt storlek
    SDL_Rect backgroundSize;
    backgroundSize.x = 0;
    backgroundSize.y = 0;
    backgroundSize.w = box.w;
    backgroundSize.h = box.h;
    SDL_Rect borderLength;
    borderLength.x = 0;
    borderLength.y = 0;
    borderLength.w = box.w -10;
    borderLength.h = 5;
    SDL_Rect borderHeight;
    borderHeight.x = 0;
    borderHeight.y = 0;
    borderHeight.w = 5;
    borderHeight.h = box.h - 10;
    
    
    //ritar ut fönstrets backgrund och ram
    apply_surface(box.x, box.y, background, screen, &backgroundSize);
    apply_surface(box.x +5, box.y, topBorder, screen, &borderLength);
    apply_surface(box.x +5, box.y+box.h - 5, bottomBorder, screen, &borderLength);
    apply_surface(box.x+box.w - 5, box.y + box.h - 5, bottomRightCorner,screen);
    apply_surface(box.x,box.y+box.h - 5, bottomLeftCorner, screen);
    apply_surface(box.x, box.y, topLeftCorner, screen);
    apply_surface(box.x+box.w -5, box.y, topRightCorner, screen);
    apply_surface(box.x, box.y + 5, leftBorder, screen, &borderHeight);
    apply_surface(box.x + box.w - 5, box.y + 5 , rightBorder, screen, &borderHeight);
    
    //ritar ut alla object som hör till detta window
    for(auto i : objects)
      {
	i->print(screen);
      }
    
  }
  
  
  bool window::loaded()
  {
    
    if(background != nullptr)
      {
	return true;
      }
    
    return false;
  }
}//slut på namnrymd
