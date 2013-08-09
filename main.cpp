#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <string>

using namespace std;
SDL_Surface* load_image(const string&);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*);

int main(int argc, char* argv[])
{
	const int SCREEN_WIDTH  = 1024;
	const int SCREEN_HEIGHT =  768;
	const int SCREEN_BPP    =   32;
	
	SDL_Surface* message = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* screen = nullptr;

	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return 1;
	
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	//SDL_SWSURFACE skapar skärmen i system minnet
	
	if( screen == nullptr)
	{
		return 1;
	}
	
	SDL_WM_SetCaption( "Hello World", nullptr);
	
	message = load_image("hello.bmp");
	if(message == nullptr)
		return 1;
	
	background = load_image("background.bmp");
	if(message == nullptr)
		return 1;
	
	apply_surface(0, 0, background, screen);
	apply_surface(500, 0, background, screen);
	apply_surface(0, 546, background, screen);
	apply_surface(500, 546, background, screen);
	apply_surface(400, 200, message, screen);
	
	if( SDL_Flip( screen ) == -1)
		return 1;
	
	SDL_Delay(4000);

	SDL_FreeSurface( background );
	SDL_FreeSurface( message );
	
	SDL_Quit();
	
	return 0;
	
}

SDL_Surface* load_image(const string& filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = nullptr;
	
	//The optimized image that will be used
	SDL_Surface* optimizedImage = nullptr;
	
	loadedImage = IMG_Load( filename.c_str() );
	
	if(loadedImage != nullptr)
	{
		//create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		
		//free the old image
		SDL_FreeSurface( loadedImage );
	}
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, nullptr, destination, &offset );
}