//#include "functions.h"
//#include <iostream>
//#include <string>
#include <stdexcept>
#include "SGS.h"

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
	Menu mainMenu(screen);  //Skapa mainMenu och länka det till skärmen
	mainMenu.load_background("Images/Gui/background.png");
	
	 mainMenu.make_textbox("ks bfeag",50,50, 300, 500);
	mainMenu.make_button("New Game",300,100,"make_new_game");
	mainMenu.make_button("Options", 300,200,"options");
	mainMenu.make_button("Exit", 300,400,"exit"); 
	mainMenu.make_checkbox(50, 50, "", false);
	
	try
	{
		mainMenu.run(); //startar programmet
	}
	catch(runtime_error re)
	{
		cout << re.what() << endl;
	}
	catch(...)
	{
		cout << "an error occured" << endl;
	}
	
	//avslut, ta bort alla surfaces som skapas (enbart screen just nu) och avsluta TTF, SDL och musiken
	cleanUp({screen});
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	
	cout << "exit OK!" << endl;
	return 0;
}
