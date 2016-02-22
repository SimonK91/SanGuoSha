//#include "functions.h"
//#include <iostream>
//#include <string>
#include <stdexcept>
#include "SGS.h"
#include "SDL/SDL_thread.h"

using namespace std;

bool quit = false;
int loading_thread(void* data)
{
  while(quit == false)
    {
      //Do the caption animation 
      SDL_WM_SetCaption( "S", NULL );
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "Sa", NULL );
      SDL_Delay( 250 ); 
      SDL_WM_SetCaption( "San", NULL ); 
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "SanG", NULL ); 
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "SanGu", NULL ); 
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "SanGuo", NULL ); 
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "SanGuoS", NULL ); 
      SDL_Delay( 250 ); 
      SDL_WM_SetCaption( "SanGuoSh", NULL ); 
      SDL_Delay( 250 );
      SDL_WM_SetCaption( "SanGuoSha", NULL ); 
      SDL_Delay( 250 );
    }
  
  return 0;
}

SDL_Thread* thread = NULL;
// SDL_Thread* gameInit = NULL;

int main(int argc, char* argv[])
{
//  thread = SDL_CreateThread(loading_thread, NULL);
	// gameInit = SDL_CreateThread(initGame,NULL);
	// Variabler i starten
	const int SCREEN_WIDTH  = 1024;
	const int SCREEN_HEIGHT = 768;
	const int SCREEN_BPP    = 32;
	try
	{
	// Initialize	
	Surface screen;
	cerr << "skapa skreen" << endl;
	screen = Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	cerr << "screen skapad" << endl;
	// Start av main	
	cerr << "mainMenu skapas" << endl;
	Menu mainMenu(screen);  //Skapa mainMenu och länka det till skärmen
	cerr << "bakgrundsbilden laddas" << endl;
	mainMenu.load_background("Images/Gui/background.png");
	cerr << "en button skapas" << endl;
	mainMenu.make_button("New Game",400,100,"make_new_game");
	mainMenu.make_button("Options", 400,200,"options");
	mainMenu.make_button("Exit", 400,400,"exit"); 
	cerr << "mainMenu startas" << endl;
	
	for(int i = 0; i < argc ; ++i)
	{
		cerr << "argument " << i << ": " << argv[i] << endl;
	}
	
		mainMenu.run(); //startar programmet
	}
	catch(runtime_error re)
	{
		cerr << re.what() << endl;
	}
	catch(logic_error le)
	{
		cerr << le.what() << endl;
	}
	catch(exception e)
	{
		cerr << e.what() << endl;
	}
	catch(...)
	{
		cerr << "an error occured" << endl;
	}
	
	//avslut, ta bort alla surfaces som skapas (enbart screen just nu) och avsluta TTF, SDL och musiken
	SDL_KillThread(thread);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	
	cerr << "exit OK!" << endl;
	return 0;
}
