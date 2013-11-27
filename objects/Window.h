#ifndef WINDOW_H
#define WINDOW_H

#include "../functions.h"
#include "Button.h"
#include "Slider.h"
#include "Textbox.h"
#include "Objects.h"
#include "Card.h"
#include <vector>


namespace Object
{
  class Window : public ActiveObject
  {
  private:
	Surface windowSurface;
    Surface background;
    SDL_Rect box;
    std::vector<Object*> objects;
	void loadBackground(int, int, int, int);
    
  public:
    //notera att  fönstret bör vara minst 10x10 pixlar stort
    Window(const int& x, const int& y, const int& w, const int& h){loadBackground(x,y,w,h);}
	~Window();
    
	unsigned getSize(){return objects.size();}
	
	Object* getObject(unsigned o)
	{
		if (o < objects.size())
		{
			return objects.at(o);
		}
		return nullptr;
	}
	
	Object* remove(unsigned o)
	{		
		if (o < objects.size())
		{
			Object* temp;
			temp = objects.at(o);
			objects.erase(objects.begin()+o);
			return temp;
		}
		return nullptr;
	}
	std::string handleEvent(const SDL_Event&);
	
    void makeButton(const std::string& text, const int& x_pos, const int& y_pos, const std::string& command = "",
					const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
    bool makeSlider(const int& x_pos, const int& y_pos, const std::string& command, const int& value);
    //void make_checkbox(/*konstruktor argument för checkBox*/){}
    bool makeTextbox(const int& x, const int& y, const int& w, const int& h,
					 const unsigned& size = 13, const std::string& font = "Fonts/LHANDW.TTF");
    void paint(Surface& screen);
	void addCard(Card* card, int xPos, int yPos);
    void setText(const int& where, const std::string& what_text);
  };  
}//namnrymd
#endif
