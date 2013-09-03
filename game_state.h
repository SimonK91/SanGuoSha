#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "functions.h"
#include "object_button.h"
#include "pointer_arrow.h"



#include <vector>

class GameState
{
private:
SDL_Surface* background;
SDL_Event event;
SDL_Surface* screen;
object::pointer_arrow arrow;

std::vector<object::object*> all_objects;

public:
	GameState(SDL_Surface* scr) : screen(scr){}
	void run();

	void load_background(const std::string& bg){background = load_image(bg);}
	void make_button(const std::string& filename, const int& x_pos, const int& y_pos, const int& w_pos = 195, const int& h_pos = 51);
	void make_textbox(const SDL_Rect dimensions, std::string text = ""); //note to simon. varför inte bara en rect istället för alla grejer ovan?
	//make_textbox är ej skriven än!
};



#endif