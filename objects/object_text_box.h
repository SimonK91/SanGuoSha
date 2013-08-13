#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "objects.h"

class text_box : public dead_object
{
private:
	SDL_Color textColor;
	TTF_Font* font;
	SDL_Surface* surface = nullptr;
public:
	~text_box()
	{
		clean_up({surface});
	}
	
	text_box(const std::string& font_style, const unsigned& size = 12, const Uint8& red = 255, const Uint8& green = 255, const Uint8& blue = 255)
		{font = TTF_OpenFont(font_style.c_str(), size); textColor = {red,green,blue,0};}

	bool loaded(){return font != nullptr;}
	void print(std::string message, int x, int y, SDL_Surface* to_where)
	{
		surface = TTF_RenderText_Solid(font, message.c_str(), textColor);
		apply_surface(x, y, surface, to_where);
	}
	
	int get_w(){if(surface != nullptr)
					return surface->w;
				return 0;}
	int get_h(){if(surface != nullptr)
					return surface->h;
				return 0;}
	bool set_font(std::string font_style, int size = 12);
};

#endif