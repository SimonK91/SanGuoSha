#ifndef POPUPTEXT_H
#define POPUPTEXT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "objects.h"
#include <string>

namespace object
{
  class PopupText : public active_object
  {
    
  private:
    TTF_Font* font;
    SDL_Surface* text_area;
    SDL_Surface* background;
    SDL_Color text_color;
    SDL_Rect box;
    
    bool show_text;
    int frame_size;
    int text_x;
    int text_y;
    int font_style;
    bool font_bold;
    bool font_italic;
    bool font_underlined;
    bool font_strike_through;
    
  public:
    PopupText(int x_pos, int y_pos, int width, int height, SDL_Color color, std::string f, unsigned font_size);
    ~PopupText();
    void setColor(std::string color);
    std::string handle_event(const SDL_Event& event);
    void  print(SDL_Surface* to_where);
    void  setFileText(std::string file, std::string keyword);
    void  setText(std::string text);
    
    
  };
  
}//namespace
#endif
