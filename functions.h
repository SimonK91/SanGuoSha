#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include <vector>

//using namespace std;

SDL_Surface* load_image(const std::string&, bool transparant = false, const Uint8& = 0, const Uint8& = 0, const Uint8& = 0, bool color_key = false);
void apply_surface(int x, int y, SDL_Surface* from_where, SDL_Surface* to_where, SDL_Rect* clip = nullptr);
SDL_Surface* Init(const int& width, const int& height, const int& Bits_Per_Pixel);
void clean_up(std::vector<SDL_Surface*> clean_surface = {}, std::vector<TTF_Font*> clean_font = {});
std::string I2S(const int&);
int S2I(const std::string&);
#endif