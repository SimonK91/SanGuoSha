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
	TTF_Font* font;
	font = TTF_OpenFont("Fonts/LHANDW.TTF",28);
		
	// Load the files
	
	//background
	background = load_image ("Images/Gui/background.png");
	// If there was a problem in loading the background
	if(background == nullptr)
		return 1;
	
	
	//text_box message("Fonts/LHANDW.TTF",28);
	//if(!message.loaded())
	//	return 1;
	
	//SDL_ShowCursor(0); //hide standard cursor
	pointer_arrow arrow("");
	if(!arrow.loaded())
		SDL_ShowCursor(1);
		
	button button_back("Images/Gui/backButton.png",100,200,195,51);
	
	button button_back2("Images/Gui/backButton.png",200,200,195,51);
	
	button button_back3("Images/Gui/backButton.png",300,200,195,51);
	
	button button_back4("Images/Gui/backButton.png",400,200,195,51);
	
	button button_back5("Images/Gui/backButton.png",500,200,195,51);
	
	//While the user hasn't quit
	while( quit == false)
	{
		SDL_Delay(17);
		apply_surface(0, 0, background, screen);
		//message.print(text,(SCREEN_WIDTH - message.get_w())/2,0,screen);
		button_back.print(screen);
		button_back2.print(screen);
		button_back3.print(screen);
		button_back4.print(screen);
		button_back5.print(screen);
		//arrow.print(screen);
		while( SDL_PollEvent( &event))
		{
			button_back.handle_events(event, arrow);
			button_back2.handle_events(event, arrow);
			button_back3.handle_events(event, arrow);
			button_back4.handle_events(event, arrow);
			button_back5.handle_events(event, arrow);
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
	clean_up({background},{font});
	TTF_Quit();
	SDL_Quit();
	return 0;
}
