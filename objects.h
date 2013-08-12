#ifndef OBJECTS_H
#define OBJECTS_H

#include "functions.h"
#include <string>

class Object
{
public:
	
private:
	
};


class pointer_arrow
{
private:
	int x;
	int y;
	SDL_Surface* image = nullptr;
public:
	~pointer_arrow(){clean_up({image});}
	pointer_arrow(std::string filename,bool transparant = true, const Uint8& red = 0, const Uint8& green = 0, const Uint8& blue = 0, bool color_key = false){image = load_image(filename,transparant,red,green,blue,color_key);}
	pointer_arrow() = default;
	pointer_arrow(const pointer_arrow&) = delete;
	pointer_arrow(const pointer_arrow&&) = delete;
	
	bool loaded(){return image != nullptr;}
	void print(SDL_Surface* to_where){apply_surface(x,y,image,to_where);}
	int get_x()const{ return x;}
	int get_y()const{ return y;}
	int get_w()const{ return image->w;}
	int get_h()const{ return image->h;}
	void update_coordinates(const SDL_Event& event){x = event.motion.x; y = event.motion.y;}
};

class text_box
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
	
	int get_w(){ if(surface != nullptr)
					return surface->w;
					return 0;}
	int get_h(){ if(surface != nullptr)
					return surface->h;
					return 0;}
	bool set_font(std::string font_style, int size = 12)
	{
		TTF_Font* temp = nullptr;
		temp = TTF_OpenFont(font_style.c_str(), size);
		if(temp == nullptr)
			return false;
		clean_up({},{font});
		font = temp;
		return true;
	}
};


#endif