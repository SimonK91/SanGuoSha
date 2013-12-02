#include "Window.h"

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
    for(int i = objects.size()-1;i >= 0 ; --i)
    {
		if(dynamic_cast<ActiveObject*>(objects.at(i)) != nullptr)
		{
			tmpCommand = dynamic_cast<ActiveObject*>(objects.at(i))->handleEvent(event2);
		}
		if(tmpCommand != "")
		{
			break;
		}
    }
    
    return tmpCommand;
    
  }
  
  
  void Window::paint(Surface& screen)
  {
    //dessa SDL_Rects används för att se till att backgrunden och ramen "skalas om" till rätt storlek
    SDL_Rect backgroundSize;
    backgroundSize.x = 0;
    backgroundSize.y = 0;
    backgroundSize.w = box.w;
    backgroundSize.h = box.h;
	windowSurface = SDL_CreateRGBSurface(0, box.w, box.h, 32,
                                   0, 0, 0, 0);
    
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
  
  bool Window::makeTextbox(const int& x, const int& y, const int& w , const int& h,
			               const unsigned& size, const std::string& font)
  {
    Textbox* temp = new Textbox(x,y,w,h,font,size);
    
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
  
  
  
	void Window::loadBackground(int x, int y, int w, int h)
	{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	background = loadImage("Images/Gui/Window/background.png", false);
	Surface tmp_bg;
	
	//övre ramen
	tmp_bg = loadImage("Images/Gui//window/tb.png",true);
	applySurface(0,0, tmp_bg, background, nullptr);
	//vänstra ramen
	tmp_bg = loadImage("Images/Gui/window/lb.png",true);
	applySurface(0,0, tmp_bg, background, nullptr);
	//nedre ramen
	tmp_bg = loadImage("Images/Gui/window/bb.png",true);
	applySurface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	//högra ramen
	tmp_bg = loadImage("Images/Gui/window/rb.png",true);
	applySurface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	//övre vänstra hörnet
	tmp_bg = loadImage("Images/Gui/window/ltc.png",true);
	applySurface(0,0, tmp_bg, background, nullptr);
	//övre högra hörnet
	tmp_bg = loadImage("Images/Gui/window/rtc.png",true);
	applySurface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	//nedre vänstra hörnet
	tmp_bg = loadImage("Images/Gui/window/lbc.png",true);
	applySurface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	//nedre högra hörnet
	tmp_bg = loadImage("Images/Gui/window/rbc.png",true);
	applySurface(w - tmp_bg->w, h - tmp_bg->h, tmp_bg, background, nullptr);
	}
  
}//slut på namnrymd
