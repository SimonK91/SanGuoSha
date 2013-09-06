#ifndef WINDOW_H
#define WINDOW_H

#include "functions.h"
#include "button.h"
#include "objects.h"
#include <vector>


namespace object
{

class window
{
private:
SDL_Surface* background = nullptr;
SDL_Surface* top_border = nullptr;
SDL_Surface* left_border = nullptr;
SDL_Surface* right_border = nullptr;
SDL_Surface* bottom_border = nullptr;
SDL_Rect box;

vector<object*> objects;
public:
 window(const int& x, const int& y, const int& w, const int& h,) : box.x(x),box.y(y),box.w(w),box.h(h)
  {
    //ladda background och borders
  }
 void handleEvents(SDL_Event event);
 void makeButton(const std::string& text, const int& xPos, const int& yPos, const std::string command = "");
 void print(SDL_Surface* screen);
};
}//namespace
