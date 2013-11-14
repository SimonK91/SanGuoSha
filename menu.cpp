#include "SGS.h"
#include "cardList.h"

using namespace object;

void Menu::run()
{
	m.play();
	Uint8 *keystates = SDL_GetKeyState(nullptr);
	std::string command;
	
	while(running) //medans programmet kÃ¶rs
	{

		while( SDL_PollEvent( &event)) //sÃ¥ lÃ¤nge som det finns en event
		{
			for(unsigned i = 0 ; i < all_objects.size() ; ++i)  //fÃ¶r varje objekt som finns i gamestatet
			{
				 //om objektet Ã¤r ett aktivt objekt och has_window är false(aktiva objekt kan manipulera saker)
				if(!has_window && dynamic_cast<active_object*>(all_objects.at(i)) != nullptr)
				{
					 //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
					command = dynamic_cast<active_object*>(all_objects.at(i))->handle_event(event);
					run_command(command);
				}
				 //annars kör enbart handle_event på window
				else if(dynamic_cast<window*>(all_objects.at(i)) != nullptr)
				{
					command = dynamic_cast<window*>(all_objects.at(i))->handle_event(event); //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
					run_command(command);
				}
			}
			
			if( event.type == SDL_QUIT)    		// om krysset uppe till hÃ¶ger blev intryckt
				running = false;      		    //
			if(keystates[SDLK_LALT] &&			// eller om alt + f4 blev intryckt
			   event.key.keysym.sym == SDLK_F4) //
				running = false;           		// avsluta programmet
		}
		paint();
		SDL_Delay(15);
	}

	if(!exit())
	{
		throw("Could not exit Menu");
	}
}


Menu::~Menu()
{
}

bool Menu::exit()
{
	try
	{
	write_settings(settings);
	while(!all_objects.empty())
	{
		delete all_objects.back();
		all_objects.pop_back();
	}
	clean_up({background});
	}
	catch(...)
	{
		return false;
	}

	return true;
}

void Menu::paint()
{
	apply_surface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	{
		all_objects.at(i)->print(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	}
	SDL_Flip(screen);                   // Skriv ut bilden pÃ¥ skÃ¤rmen
}

#include "menu_commands.cpp" //enbart fÃ¶r att separera upp alla commands till en annan cpp fil, (detta Ã¤r ej nÃ¶dvÃ¤ndigt att gÃ¶ra)