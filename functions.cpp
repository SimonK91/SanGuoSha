#include "functions.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;
SDL_Surface* load_image(const string& filename,bool transparant, const Uint8& red, const Uint8& green, const Uint8& blue, bool color_key)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = nullptr;
	
	//The optimized image that will be used
	SDL_Surface* optimizedImage = nullptr;
	
	// laddar in bilden till temporära
	loadedImage = IMG_Load( filename.c_str() );
	if(loadedImage != nullptr)
	{
		if(transparant)
			optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
		else
		{
			//create an optimized image
			optimizedImage = SDL_DisplayFormat( loadedImage );
				
			//set color key if added colors
			if(color_key)
			{
				Uint32 colorkey = SDL_MapRGB( optimizedImage->format, red, green, blue );
				SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
			}
		}
		//free the old image
		SDL_FreeSurface( loadedImage );
	}
	
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface* Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT, const int& SCREEN_BPP)
{
	SDL_Surface* screen;

	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return nullptr;
	}
	
	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	//If there was an error in setting up the screen
	if (screen == nullptr)
	{
		return nullptr;
	}
	
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		return nullptr;
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "SanGuoSha", nullptr);
	
	//If everything is ok
	return screen;
}

void clean_up(std::vector<SDL_Surface*> clean_surface, std::vector<TTF_Font*> clean_font)
{
	for(auto it = clean_surface.begin(); it != clean_surface.end(); ++it)
		SDL_FreeSurface(*it);
		
	for(int i = 0 ; i < clean_font.size(); ++i)
		TTF_CloseFont(clean_font.at(i));

}

//Integer to string
std::string I2S(const int& i)
{
	std::stringstream ss;
	ss << i;
	std::string s = ss.str();
	return s;
}
