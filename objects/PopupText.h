#ifndef POPUPTEXT_H
#define POPUPTEXT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Objects.h"
#include <string>

namespace Object
{
  class PopupText : public ActiveObject
  {
    
  private:
    TTF_Font* font;
    Surface text_area;
    Surface background;
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
    std::string handleEvent(const SDL_Event& event);
    void  paint(Surface to_where);
    void  setFileText(std::string file, std::string keyword);
    void  setText(std::string text);
    
    
  };
  
}//namespace
#endif
