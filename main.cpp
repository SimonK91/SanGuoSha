#include "functions.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	// Variabler i starten
	const int SCREEN_WIDTH  = 800;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP    = 32;
	
	SDL_Surface* background = nullptr;
	SDL_Surface* message = nullptr;
	SDL_Surface* screen = nullptr;
	
	SDL_Event event;
	
	TTF_Font* font = nullptr;
	SDL_Color textColor;
	textColor = {255,255,255};

	
	// Start av main
	bool quit = false;
	
	// Initialize
	screen = Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	if( screen == nullptr )
		return 1;
	
	// Load the files
	background = load_image ("Images/Gui/background.png");
	
	// If there was a problem in loading the background
	if(background == nullptr)
	{
		return 1;
	}
	
	//open the font
	font = TTF_OpenFont("Fonts/LHANDW.TTF", 28);
	
	//If there was an error in loading the font
	if(font == nullptr)
	{
		clean_up({background});
		return 1;
	}
		

	//Render the text
	message = TTF_RenderText_Solid( font, "The quick brown lalalala", textColor);
	
	if( message == nullptr)
	{
		return 1;
	}
	
	// Apply the surface to the screen
	apply_surface(0, 0, background, screen);
	apply_surface(0, 150, message, screen);
	
	// Update the screen
	if( SDL_Flip( screen ) == -1)
	{
		return 1;
	}
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
	clean_up({background},{font});
	
	return 0;
}
