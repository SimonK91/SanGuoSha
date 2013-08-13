#ifndef POINTER_ARROW_H
#define POINTER_ARROW_H

#include "../functions.h"

namespace object
{
class pointer_arrow
{
private:
	int x,y;
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
	void update_coordinates(const SDL_Event& event);
};

}//slut på namnrymden

#endif
