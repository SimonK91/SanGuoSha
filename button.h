#ifndef BUTTON_H
#define BUTTON_H

#include "functions.h"
#include "objects.h"
#include <string>

class button
{
private:
	SDL_Rect box;
	SDL_Rect clip[4];
	int active;
	SDL_Surface* buttonSheet = nullptr;
public:
	button(std::string image, int x, int y, int w, int h);
	
	bool inside( const pointer_arrow&);
	void handle_events(const SDL_Event&, const pointer_arrow&);
	
	void show(SDL_Surface*);
};


#endif