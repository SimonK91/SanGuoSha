#ifndef OBJECTS_H
#define OBJECTS_H

#include "functions.h"
#include <string>

class pointer_arrow
{
private:
	int x;
	int y;
	SDL_Surface* image = nullptr;
public:
	~pointer_arrow(){clean_up({image});}
	pointer_arrow(std::string filename, int red = -1, int green = -1, int blue = -1){image = load_image(filename,red,green,blue);}
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
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
public:
	~text_box()
	{
		clean_up({surface});
	}
	
	text_box(std::string font_style, int size = 12, int red = 255, int green = 255, int blue = 255)
		{font = TTF_OpenFont(font_style.c_str(), size); textColor = {red,green,blue};}

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