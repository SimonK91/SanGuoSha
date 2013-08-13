#ifndef BUTTON_H
#define BUTTON_H

#include "objects.h"
//#include "../functions.h"
#include <string>

namespace object
{
class button : public active_object
{
private:
	std::vector<SDL_Rect> clip;
	SDL_Surface* buttonSheet = nullptr;
	std::string value;
	
	
public:
	button(std::string image, int x, int y, int w, int h);
	~button(){clean_up({buttonSheet});}
	
	std::string get_value(){return value;}
	void set_value(std::string s){value = s;}
	bool inside( const pointer_arrow&);
	bool inside( const int& x, const int& y);
	bool handle_event( const SDL_Event&, const pointer_arrow&);
	bool loaded();
	
	void print(SDL_Surface*);
};

}//slut på namnrymden
#endif