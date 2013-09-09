#include "object_window.h"

namespace object
{
  void window::makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string& command,const std::string& image, const unsigned& size)
  {
    button* tmp = new button(text, xPos, yPos, command, image, size);
    objects.push_back(tmp);
  } 
  
  window::~window()
  {
    clean_up( {background});//,topBorder,bottomBorder,leftBorder,rightBorder,bottomRightCorner,bottomLeftCorner,topRightCorner, topLeftCorner},{});
    
    for(auto i : objects)
      {
	delete i;
      }
  }  
  
  std::string window::handle_event(const SDL_Event& event, const pointer_arrow& arrow )
  {
	pointer_arrow arrow2;
	arrow2.set_x(arrow.get_x()-box.x);
	arrow2.set_y(arrow.get_y()-box.y);
    std::string tmpCommand = "";
    for(auto i: objects)
    {
		if(dynamic_cast<active_object*>(i) != nullptr)
		{
			tmpCommand =  dynamic_cast<active_object*>(i)->handle_event(event, arrow2);
		}
		if(tmpCommand != "")
			break;
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
    
	//ritar ut alla object som hör till detta window
    for(auto i : objects)
      {
	i->print(background);
      }
    
    //ritar ut fönstrets backgrund och ram
    apply_surface(box.x, box.y, background, screen, &backgroundSize);
    
    
  }
  bool window::makeSlider(const int& x_pos, const int& y_pos, const std::string& command)
{
	slider* temp = new slider(x_pos, y_pos, command);
	if (temp == nullptr)
		return false;
	objects.push_back(temp);
	return true;
}

bool window::makeTextBox(const std::string& text, const int& x, const int& y, const int& w , const int& h
							,const SDL_Color &col, const std::string& font, const unsigned& size)
{
	text_box* temp = new text_box(text,x,y,w,h,col,font,size);
	
	if (temp == nullptr)
		return false;
	objects.push_back(temp);
	//all_objects.pop_back();
	return true;
	
}
}//slut på namnrymd
