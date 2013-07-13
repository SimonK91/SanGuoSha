#include "SDL/SDL.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Surface* picture = NULL;
	SDL_Surface* screen  = NULL;
	
	SDL_Init( SDL_INIT_EVERYTHING) ;
	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	
	picture = SDL_LoadBMP("mypic.bmp");
	
	SDL_BlitSurface( picture, NULL, screen, NULL );
	
	SDL_Flip( screen );
	
	SDL_Delay( 2000 );
	
	SDL_FreeSurface( picture );
	
	SDL_Quit();
	
	return 0;
}