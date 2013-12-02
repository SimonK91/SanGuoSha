#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

//using namespace std;

class SGS_error : public std::runtime_error
{
public:
	SGS_error(std::string text) : runtime_error(text){}
};

SDL_Surface* loadImage(const std::string&, bool transparant = false, const Uint8& = 0, const Uint8& = 0, const Uint8& = 0, bool color_key = false);

class Surface
{
private:
	SDL_Surface* image;
	std::string name;
public:
	//konstruktorer
	Surface() : image(nullptr){}
	Surface(std::string name_) : image(nullptr),name(name_) {}
	Surface(const Surface& surface)
	{
		if(surface.name == "screen")
			image = surface.image;
		else
			image = loadImage(surface.name);
		name = surface.name;
	}
	Surface(Surface&& surface){ setImage(surface); }
	~Surface(){ if(image != nullptr) SDL_FreeSurface(image); }
	Surface& operator=(SDL_Surface*);
	Surface& operator=(const Surface& surface)
	{
		image = loadImage(surface.name);
		name = surface.name;
		return *this;
	}
	Surface& operator=(Surface&& surface)
	{
		image = surface.image;
		name = surface.name;
		surface.image = nullptr;
		surface.name = "";
		return *this;
	}
	SDL_Surface* operator->(){return image;}
	
	SDL_Surface* getImage(){return image;}
	void setImage(Surface);//{image = tmp;}
	void setImage(SDL_Surface*);//{image = tmp;}
	std::string getName(){return name;}
	void setName(std::string imageName){ name = imageName; }
};

void applySurface(int x, int y, Surface& from_where, Surface& to_where, SDL_Rect* clip = nullptr);
Surface Init(const int& width, const int& height, const int& Bits_Per_Pixel);
void cleanUp(std::vector<TTF_Font*> clean_font = {});
std::string I2S(const int&);
int S2I(const std::string&);

bool loadSettings( std::vector<std::pair<std::string, std::string>>&);
bool writeSettings(std::vector<std::pair<std::string, std::string>>);

#endif
