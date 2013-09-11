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
	
	mainMenu.make_textbox("<b>aa<u>aa</u>bb</b> <s>bbb</s> b fds afd asf sda ghfdsjalh flkdfh sa gff jakl fhf gf hjasb b vh vnans djf a fdsaf ökankvjshldaf skdnf vlsahflgjkasdfj bjdsgafjbn vbscjhag djsabvsdytyuerabreab hdsgayfyeurb bfeakgbfasrgyea bfeag",50,50, 300, 500);
	mainMenu.make_button("New Game",300,100,"make_new_game");
	mainMenu.make_button("Options", 300,200,"options");
	mainMenu.make_button("Exit", 300,400,"exit");
	mainMenu.run(); //startar programmet
	//delete &mainMenu;
	//avslut, ta bort alla surfaces som skapas (enbart screen just nu) och avsluta TTF, SDL och musiken
	clean_up({screen});
    Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
