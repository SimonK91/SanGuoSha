#ifndef STRINGINPUT_H
#define STRINGINPUT_H
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"



class StringInput
{
 private:
  //storage string
  std::string str;
  
  //text surface
  SDL_Surface* text;

  TTF_Font* font;
  SDL_Color textColor;
  
public:

  //init variablers
  StringInput();
  
  ~StringInput();

  void handleInput(SDL_Event& userEvent);
  
  void showCentered(SDL_Surface* screen);
  std::string getStr();
  void clear();
};

#endif
