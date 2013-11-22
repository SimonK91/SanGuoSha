#include "Window.h"
#include <algorithm>

namespace Object
{
  void Window::makeButton(const std::string& text, const int& x_pos, const int& y_pos, const std::string& command,const std::string& image, const unsigned& size)
  {
    Button* tmp = new Button(text, x_pos, y_pos, command, image, size);
    objects.push_back(tmp);
  } 
  
  Window::~Window()
  {
    for(auto i : objects)
    {
		delete i;
    }
  }  
  
  std::string Window::handleEvent(const SDL_Event& event)
  {
    SDL_Event event2 = event;
	event2.motion.x -= box.x;
	event2.motion.y -= box.y;
    std::string tmpCommand = "";
	std::string command = "";
	
    for(auto i: objects)
    {
		if(dynamic_cast<ActiveObject*>(i) != nullptr)
			tmpCommand = dynamic_cast<ActiveObject*>(i)->handleEvent(event2);
		if(tmpCommand != "")
		{
			command = tmpCommand;
			//destory the event!
			event2.motion.x *= -1;
			event2.motion.y *= -1;
		}
	}
    return command;
  }
  
  
  void Window::paint(Surface& screen)
  {
    //dessa SDL_Rects används för att se till att backgrunden och ramen "skalas om" till rätt storlek
    SDL_Rect backgroundSize;
	backgroundSize.x = 0;
    backgroundSize.y = 0;
    backgroundSize.w = box.w;
    backgroundSize.h = box.h;
    
	//rita ut bakgrunden på bilden
	applySurface(0, 0, background, windowSurface);
	
    //ritar ut alla Object som hör till detta window
    for(auto i : objects)
    {
		i->paint(windowSurface);
    }
    
    //ritar ut fönstret på skärmen
    applySurface(box.x, box.y, windowSurface, screen, &backgroundSize);
  }
  
  bool Window::makeSlider(const int& x_pos, const int& y_pos, const std::string& command, const int& value)
  {
    Slider* temp = new Slider(x_pos, y_pos, command, value);
    if (temp == nullptr)
		return false;
    objects.push_back(temp);
    return true;
  }
  
  bool Window::makeTextbox(const std::string& text, const int& x, const int& y, const int& w , const int& h
			     ,const SDL_Color &col, const std::string& font, const unsigned& size)
  {
    Textbox* temp = new Textbox(text,x,y,w,h,col,font,size);
    
    if (temp == nullptr)
      return false;
    objects.push_back(temp);
    //all_objects.pop_back();
    return true;
    
  }
  void Window::setText(const int& where, const std::string& what_text)
  {
    if(dynamic_cast<Textbox*>(objects.at(where)) != nullptr)
      dynamic_cast<Textbox*>(objects.at(where))->setText(what_text);
  }
  void Window::addCard(Card* card, int xPos, int yPos)
  {
    objects.push_back(card);
	card->setPosition(xPos,yPos);
	
  }
}//slut på namnrymd
