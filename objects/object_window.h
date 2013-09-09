#ifndef WINDOW_H
#define WINDOW_H

#include "../functions.h"
#include "object_button.h"
#include "object_slider.h"
#include "object_text_box.h"
#include "objects.h"
#include <vector>


namespace object
{
  class window : public active_object
  {
  private:
    SDL_Surface* background = nullptr;/*
    SDL_Surface* topBorder = nullptr;
    SDL_Surface* leftBorder = nullptr;
    SDL_Surface* rightBorder = nullptr;
    SDL_Surface* bottomBorder = nullptr;
    SDL_Surface* bottomRightCorner = nullptr;
    SDL_Surface* bottomLeftCorner = nullptr;
    SDL_Surface* topLeftCorner = nullptr;
    SDL_Surface* topRightCorner = nullptr;*/
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
	SDL_Surface* tmp_bg;
	
	//övre ramen
	tmp_bg = load_image("Images/Gui//window/tb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//vänstra ramen
	tmp_bg = load_image("Images/Gui/window/lb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre ramen
	tmp_bg = load_image("Images/Gui/window/bb.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//högra ramen
	tmp_bg = load_image("Images/Gui/window/rb.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//övre vänstra hörnet
	tmp_bg = load_image("Images/Gui/window/ltc.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//övre högra hörnet
	tmp_bg = load_image("Images/Gui/window/rtc.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre vänstra hörnet
	tmp_bg = load_image("Images/Gui/window/lbc.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre högra hörnet
	tmp_bg = load_image("Images/Gui/window/rbc.png",true);
	apply_surface(w - tmp_bg->w, h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});/*
	topBorder = load_image("Images/Gui/Window/tb.png", false);
	bottomBorder = load_image("Images/Gui/Window/bb.png", false);
	bottomRightCorner = load_image("Images/Gui/Window/rbc.png", false);
	bottomLeftCorner = load_image("Images/Gui/Window/lbc.png", false);
	topLeftCorner = load_image("Images/Gui/Window/ltc.png", false);
	topRightCorner = load_image("Images/Gui/Window/rtc.png", false);
	leftBorder = load_image("Images/Gui/Window/lb.png", false);
	rightBorder = load_image("Images/Gui/Window/rb.png", false);
	
    apply_surface(0, 0, topBorder, background);
    apply_surface(0, 0, leftBorder, background);
    apply_surface(box.w - rightBorder->w, 0 , rightBorder, background);
    apply_surface(0, box.h - bottomBorder->h, bottomBorder, background);
	
    apply_surface(box.w - bottomRightCorner->w, box.h - bottomRightCorner->h, bottomRightCorner,background);
    apply_surface(0, box.h - bottomRightCorner->h, bottomLeftCorner, background);
    apply_surface(0, 0, topLeftCorner, background);
    apply_surface(box.w -bottomRightCorner->w, 0, topRightCorner, background);*/
      }
    ~window();
    std::string handle_event(const SDL_Event&, const pointer_arrow&);
    void makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string& command = "",
					const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
    bool makeSlider(const int& x_pos, const int& y_pos, const std::string& command);
    void makeCheckBox(/*konstruktor argument för checkBox*/){}
    bool makeTextBox(const std::string& text, const int& x, const int& y, const int& w, const int& h,
					  const SDL_Color &col = {255,255,255,0}, const std::string& font = "Fonts/LHANDW.TTF", const unsigned& size = 13);
    void print(SDL_Surface* screen);
  };  
}//namnrymd
#endif
