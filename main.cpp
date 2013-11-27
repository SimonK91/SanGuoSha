#include "Functions.h"
#include <iostream>
#include <string>
#include "SGS.h"
#include "sgsServer.h"

using namespace std;

int network_thread(void* data);
//global test variabel ska fixas
bool quit_network = false;
SDL_Thread* thread = NULL;
SgsServer network;


int main(int argc, char* argv[])
{
	// Variabler i starten
	const int SCREEN_WIDTH  = 800;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP    = 32;
	
	//nätverkstråden

	
	// Initialize	
	SDL_Surface* screen = nullptr;
	screen = Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	if( screen == nullptr )
		return 1;
	
	// Start av main	
	Menu mainMenu(screen);  //Skapa mainMenu och lÃ¤nka det till skÃ¤rmen
	mainMenu.load_background("Images/Gui/background.png");
	
	 mainMenu.make_textbox("ks bfeag",50,50, 450, 450);
	mainMenu.make_button("New Game",300,100,"make_new_game");
	mainMenu.make_button("Options", 300,200,"options");
	mainMenu.make_button("Exit", 300,400,"exit"); 
	//mainMenu.make_checkbox(50, 50, "", false);
	mainMenu.make_textbox("", 50, 530,450, 50);
	
	//skapar tråden för nätverk
	thread = SDL_CreateThread(network_thread, NULL);
	
	try
	{
		mainMenu.run(); //startar programmet
	}
	catch(...)
	{
		cout << "an error occured" << endl;
	}
	
	//avslut, ta bort alla surfaces som skapas (enbart screen just nu) och avsluta TTF, SDL och musiken
	quit_network = true;
	SDL_KillThread(thread);
	cleanUp({screen});
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	
	cout << "exit OK!" << endl;
	return 0;
}

int network_thread(void* data)
{
  
  
  while(quit_network == false)
    {
      network.run();
    }


  return 0;
}
