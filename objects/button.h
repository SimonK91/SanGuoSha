#ifndef BUTTON_H
#define BUTTON_H

#include "objects.h"
#include "../functions.h"
#include <string>

class button
{
private:
	SDL_Rect box;
	SDL_Rect clip[4];
	int active;
	SDL_Surface* buttonSheet = nullptr;
	std::string value;
public:
	button(std::string image, int x, int y, int w, int h);
	
	std::string get_value(){return value;}
	void set_value(std::string s){value = s;}
	
	bool inside( const pointer_arrow&);
	bool inside( const int& x, const int& y);
	bool handle_events(const SDL_Event&, const pointer_arrow&);
	
	void print(SDL_Surface*);
};


#endif