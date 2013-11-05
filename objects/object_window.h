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
    SDL_Surface* background = nullptr;
    SDL_Rect box;
    std::vector<object*> objects;
    
  public:
    //notera att  f�nstret b�r vara minst 10x10 pixlar stort
    window(const int& x, const int& y, const int& w, const int& h)
      {
	//ladda background och borders
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	background = load_image("Images/Gui/Window/background.png", false);
	SDL_Surface* tmp_bg;
	
	//�vre ramen
	tmp_bg = load_image("Images/Gui//window/tb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//v�nstra ramen
	tmp_bg = load_image("Images/Gui/window/lb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre ramen
	tmp_bg = load_image("Images/Gui/window/bb.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//h�gra ramen
	tmp_bg = load_image("Images/Gui/window/rb.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//�vre v�nstra h�rnet
	tmp_bg = load_image("Images/Gui/window/ltc.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//�vre h�gra h�rnet
	tmp_bg = load_image("Images/Gui/window/rtc.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre v�nstra h�rnet
	tmp_bg = load_image("Images/Gui/window/lbc.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre h�gra h�rnet
	tmp_bg = load_image("Images/Gui/window/rbc.png",true);
	apply_surface(w - tmp_bg->w, h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	
      }
    ~window();
    std::string handle_event(const SDL_Event&);
    void make_button(const std::string& text, const int& x_pos, const int& y_pos, const std::string& command = "",
					const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
    bool make_slider(const int& x_pos, const int& y_pos, const std::string& command, const int& value);
    //void make_checkbox(/*konstruktor argument f�r checkBox*/){}
    bool make_text_box(const std::string& text, const int& x, const int& y, const int& w, const int& h,
					  const SDL_Color &col = {255,255,255,0}, const std::string& font = "Fonts/LHANDW.TTF", const unsigned& size = 13);
    void print(SDL_Surface* screen);
	void set_text(const int& where, const std::string& what_text);
  };  
}//namnrymd
#endif
