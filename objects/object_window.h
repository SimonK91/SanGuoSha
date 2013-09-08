#ifndef WINDOW_H
#define WINDOW_H

#include "../functions.h"
#include "object_button.h"
#include "objects.h"
#include <vector>


namespace object
{
  class window : public active_object
  {
  private:
    SDL_Surface* background = nullptr;
    SDL_Surface* topBorder = nullptr;
    SDL_Surface* leftBorder = nullptr;
    SDL_Surface* rightBorder = nullptr;
    SDL_Surface* bottomBorder = nullptr;
    SDL_Surface* bottomRightCorner = nullptr;
    SDL_Surface* bottomLeftCorner = nullptr;
    SDL_Surface* topLeftCorner = nullptr;
    SDL_Surface* topRightCorner = nullptr;
    SDL_Rect box;
    
    std::vector<object*> objects;
  public:
    //notera att  fönstret bör vara minst 10x10 pixlar stort
    window(const int& x, const int& y, const int& w, const int& h)
      {
	//ladda background och borders
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	background = load_image("Images/Gui/Window/background.png", false);
	topBorder = load_image("Images/Gui/Window/tb.png", false);
	bottomBorder = load_image("Images/Gui/Window/bb.png", false);
	bottomRightCorner = load_image("Images/Gui/Window/rbc.png", false);
	bottomLeftCorner = load_image("Images/Gui/Window/lbc.png", false);
	topLeftCorner = load_image("Images/Gui/Window/ltc.png", false);
	topRightCorner = load_image("Images/Gui/Window/rtc.png", false);
	leftBorder = load_image("Images/Gui/Window/lb.png", false);
	rightBorder = load_image("Images/Gui/Window/rb.png", false);
      }
    ~window();
    std::string handle_event(const SDL_Event&, const pointer_arrow&);
    void makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string command = "");
    void makeSlider(/*konstruktor argument för slider*/);
    void makeCheckBox(/*konstruktor argument för checkBox*/);
    void makeTextBox(/*konstruktor argument för textbox*/);
    void print(SDL_Surface* screen);
    bool loaded();
  };  
}//namnrymd
#endif
