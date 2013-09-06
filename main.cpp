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
	GameState mainMenu(screen);  //Skapa mainMenu och länka det till skärmen
	
	mainMenu.load_background("Images/Gui/background.png");
	mainMenu.make_button("New Game",300,200,"make_new_game");
	mainMenu.make_button("Leakage?", 300,300,"test_leaks");
	mainMenu.make_slider(50,50,"sound");
	
	mainMenu.make_button("Delete",300,100,"delete_button");
	mainMenu.run(); //startar programmet
	
	
	//avslut, ta bort alla surfaces som skapas (enbart screen just nu) och avsluta TTF och SDL
	clean_up({screen});
	TTF_Quit();
	SDL_Quit();
	return 0;
}
