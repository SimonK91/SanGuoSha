#include "functions.h"
#include "objects.h"
#include <iostream>
#include <string>
#include "button.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Variabler i starten
	const int SCREEN_WIDTH  = 800;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP    = 32;
	
	// Initialize	
	SDL_Surface* screen = nullptr;
	screen = Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	if( screen == nullptr )
		return 1;
	
	
	// Start av main
	
	SDL_Surface* background = nullptr;
	SDL_Event event;
	
	bool quit = false;
	string text;
		
	// Load the files
	
	//background
	background = load_image ("Images/Gui/background.png");
	// If there was a problem in loading the background
	if(background == nullptr)
		return 1;
	
	
	text_box message("Fonts/LHANDW.TTF",28);
	//if(!message.loaded())
	//	return 1;
	
	SDL_ShowCursor(0); //hide standard cursor
	pointer_arrow arrow("Images/Gui/pointer.png",255,255,255);
	if(!arrow.loaded())
		return 1;
		
	button back("Images/Gui/backButton.png",400,504,195,51);
	
	//While the user hasn't quit
	while( quit == false)
	{
		apply_surface(0, 0, background, screen);
		message.print(text,(SCREEN_WIDTH - message.get_w())/2,0,screen);
		arrow.print(screen);
		back.show(screen);
		while( SDL_PollEvent( &event))
		{
			back.handle_events(event, arrow);
			if( event.type == SDL_KEYDOWN)
			{
				switch( event.key.keysym.sym)
				{
				case SDLK_ESCAPE: quit = true; break;
				
				case SDLK_SPACE: text += " "; break;
				case SDLK_BACKSPACE: if(text.size()>0)text.erase(text.end()-1,text.end()); break;
				default: text += SDL_GetKeyName(event.key.keysym.sym);
				}
			}
			if( event.type == SDL_MOUSEMOTION)
			{
				arrow.update_coordinates(event);
			}
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
		}
		if( SDL_Flip( screen ) == -1)
		{
			return 1;
		}
	}
	clean_up({background});
	TTF_Quit();
	SDL_Quit();
	return 0;
}
