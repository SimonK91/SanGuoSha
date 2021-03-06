#include "SGS.h"
using namespace Object;

void Menu::run()
{
	m.play();
	Uint8 *keystates = SDL_GetKeyState(nullptr);
	std::string command;

	//CardList* card_deck = new CardList("hero_deck");
	//CardList* discard_deck = new CardList("empty");
	//Card* card;
	//	run_command("set_settings");
	fps.setFPS(30);
	
	fps.start();
	while(running) //medans programmet kÃ¶rs
	{
	// std::cout << "kollar events" << std::endl;
		while( SDL_PollEvent( &event)) //sÃ¥ lÃ¤nge som det finns en event
		{
		// std::cout << "för varje objekt" << std::endl;
			for(unsigned i = 0 ; i < all_objects.size() ; ++i)  //fÃ¶r varje objekt som finns i gamestatet
			{
				 //om objektet Ã¤r ett aktivt objekt och has_window är false(aktiva objekt kan manipulera saker)
				if(!has_window && dynamic_cast<ActiveObject*>(all_objects.at(i)) != nullptr)
				{
					 //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
					command = dynamic_cast<ActiveObject*>(all_objects.at(i))->handleEvent(event);
					run_command(command);	
				}
				 //annars kör enbart handle_event på window
				else if(dynamic_cast<Window*>(all_objects.at(i)) != nullptr)
				{
					command = dynamic_cast<Window*>(all_objects.at(i))->handleEvent(event); //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
					run_command(command);
				}
			}
			// std::cout << "om programmet ska stängas" << std::endl;
			if( event.type == SDL_QUIT)    		// om krysset uppe till hÃ¶ger blev intryckt
				running = false;      		    //
			if(keystates[SDLK_LALT] &&			// eller om alt + f4 blev intryckt
			   event.key.keysym.sym == SDLK_F4) //
				running = false;           		// avsluta programmet
		}
		// std::cout << "första while-satsen avslutas" << std::endl;
		// if(card_deck -> empty())
		// {
			// std::swap(card_deck,discard_deck);
			// card_deck -> shuffle();
		// }
		// std::cout << "utskrift startar" << std::endl;
		if(running)
		{
			//card = card_deck -> drawCard();
			//card -> setPosition(10,10);
			// std::cout << "paint körs" << std::endl;
			paint();
			// std::cout << "paint klar" << std::endl;
			//dynamic_cast<HeroCard*>(card) -> paint(screen);
			//discard_deck -> pushBottom(card);
			// std::cout << "flip image" << std::endl;
			SDL_Flip(screen.getImage());
			// std::cout << "flip image klar" << std::endl;
			// std::cout << "delay klar" << std::endl;
		}
		fps.regulateFPS();
	}

	//delete card_deck;
	//delete discard_deck;
	if(!exit())
	{
		throw("Could not exit Menu");
	}
}

bool Menu::exit()
{
	try
	{
	writeSettings(settings);
	while(!all_objects.empty())
	{
		delete all_objects.back();
		all_objects.pop_back();
	}
	}
	catch(...)
	{
		return false;
	}

	return true;
}
void Menu::paint()
{
	// std::cout << "paint: bakgrunden skrivs ut" << std::endl;
	applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
	// std::cout << "paint: klar" << std::endl;
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	{
		all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	}
	//SDL_Flip(screen);                   // Skriv ut bilden pÃ¥ skÃ¤rmen
}

#include "menu_commands.cpp" //enbart fÃ¶r att separera upp alla commands till en annan cpp fil, (detta Ã¤r ej nÃ¶dvÃ¤ndigt att gÃ¶ra)
