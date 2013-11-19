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
    Surface background;
    SDL_Rect box;
    std::vector<Object*> objects;
    
  public:
    //notera att  fönstret bör vara minst 10x10 pixlar stort
    Window(const int& x, const int& y, const int& w, const int& h)
      {
	//ladda background och borders
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
    ~Window();
    std::string handleEvent(const SDL_Event&);
    void makeButton(const std::string& text, const int& x_pos, const int& y_pos, const std::string& command = "",
					const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
    bool makeSlider(const int& x_pos, const int& y_pos, const std::string& command, const int& value);
    //void make_checkbox(/*konstruktor argument för checkBox*/){}
    bool makeTextbox(const std::string& text, const int& x, const int& y, const int& w, const int& h,
					  const SDL_Color &col = {255,255,255,0}, const std::string& font = "Fonts/LHANDW.TTF", const unsigned& size = 13);
    void paint(Surface& screen);
	void addCard(Card* card, int xPos, int yPos);
    void setText(const int& where, const std::string& what_text);
  };  
}//namnrymd
#endif
