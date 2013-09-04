//#include "functions.h"
//#include <iostream>
//#include <string>
#include "game_state.h"

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
	
	
	bool quit = false;
		
	GameState mainMenu(screen);
	mainMenu.load_background("Images/Gui/background.png");
	
	mainMenu.make_button("Exit",300,500,"exit");
	mainMenu.make_button("Options",300,300,"make_options");
	mainMenu.make_button("Credits",300,400,"make_credits");
	mainMenu.make_button("New Game",300,200,"make_new_game");
	
	//mainMenu.make_textBox("hej mr.universium!",10,10,200,300);
	//mainMenu.make_text_box();
	mainMenu.run();
	

	TTF_Quit();
	SDL_Quit();
	return 0;
}
