#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <string>

using namespace std;
SDL_Surface* load_image(const string&);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
SDL_Surface* Init(const int& width, const int& height, const int& Bits_Per_Pixel);
void clean_up(initializer_list<SDL_Surface*>);

int main(int argc, char* argv[])
{
	// Variabler i starten
	const int SCREEN_WIDTH  = 800;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP    =  32;
	
	SDL_Surface* image = nullptr;
	SDL_Surface* screen = nullptr;
	
	SDL_Event event;
	
	
	// Start av main
	bool quit = false;
	
	// Initialize
	screen = Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	if( screen == nullptr )
		return 1;
	
	// Load the files
	image = load_image ("Images/Gui/background.png");
	if(image == nullptr)
		return 1;
	
	// Apply the surface to the screen
	apply_surface(0, 0, image, screen);
	
	// Update the screen
	if( SDL_Flip( screen ) == -1)
		return 1;
	
	//While the user hasn't quit
	while( quit == false)
	{
		while( SDL_PollEvent( &event))
		{
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
		}
	}
	clean_up({image});
	
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

SDL_Surface* Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT, const int& SCREEN_BPP)
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
		return nullptr;
	
	//Set up the title of the program
	SDL_WM_SetCaption( "Hello World", nullptr);
	
	
	//Set up the screen
	SDL_Surface* screen;	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	//If there was an error in setting up the screen
	if (screen == nullptr)
		return nullptr;
	
	
	//If everything is ok
	return screen;
}

void clean_up(initializer_list<SDL_Surface*> cleanup)
{
	for(auto it = cleanup.begin(); it != cleanup.end(); ++it)
		SDL_FreeSurface(*it);
		
	SDL_Quit();
}