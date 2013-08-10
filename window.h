#ifndef WINDOW_H
#define WINDOW_H

#include "functions.h"
#include "button.h"
#include "objects.h"

#include <vector>
class window
{
private:
SDL_Surface* background = nullptr;
SDL_Surface* top_boarder = nullptr;
SDL_Surface* left_boarder = nullptr;
SDL_Surface* right_boarder = nullptr;
SDL_Surface* bottom_boarder = nullptr;
SDL_Rect box;

vector<button> your_buttons;
vector<text_box> your_text;
public:
	window(const int& x, const int& y, const int& w, const int& h,) : box.x(x),box.y(y),box.w(w),box.h(h){}
	
	
	

};