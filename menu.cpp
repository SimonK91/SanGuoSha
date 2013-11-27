#include "SGS.h"
#include "FrameRateFixer.h"

using namespace Object;

void Menu::run()
{
	m.play();
	Uint8 *keystates = SDL_GetKeyState(nullptr);
	std::string command;

	CardList* card_deck1 = new CardList("hero_deck");
	CardList* card_deck2 = new CardList("hero_deck");
	
	CardList* discard_deck1 = new CardList("empty");
	CardList* discard_deck2 = new CardList("empty");
	
	Card* card1;
	Card* card2;
	
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
		if(card_deck1 -> empty())
		{
			std::swap(card_deck1,discard_deck1);
			card_deck1 -> shuffle();
			
			unsigned seed = card_deck1 -> getSeed();
			
			std::swap(card_deck2,discard_deck2);
			card_deck2 -> shuffle(seed);
		}
		// std::cout << "utskrift startar" << std::endl;
		if(running)
		{
			// std::cout << "ska dra kort.." << std::endl;
			card1 = card_deck1 -> drawCard();
			card2 = card_deck2 -> drawCard();
			// std::cout << "kort dragna" << std::endl;
			card1 -> setPosition(10,10);
			card2 -> setPosition(210,10);
			// std::cout << "paint körs" << std::endl;
			paint();
			// std::cout << "paint klar" << std::endl;
			// dynamic_cast<HeroCard*>(card1) -> paint(screen);
			// dynamic_cast<HeroCard*>(card2) -> paint(screen);
			discard_deck1 -> pushBottom(card1);
			discard_deck2 -> pushBottom(card2);

			// std::cout << "flip image" << std::endl;
			SDL_Flip(screen.getImage());
			// std::cout << "flip image klar" << std::endl;
			// std::cout << "delay klar" << std::endl;
		}
		
		fps.regulateFPS();
	}

	delete card_deck1;
	delete card_deck2;
	delete discard_deck1;
	delete discard_deck2;
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
	// std::cout << "paint: 'klar" << std::endl;
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	{
		all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	}
	//SDL_Flip(screen);                   // Skriv ut bilden pÃ¥ skÃ¤rmen
}

#include "menu_commands.cpp" //enbart fÃ¶r att separera upp alla commands till en annan cpp fil, (detta Ã¤r ej nÃ¶dvÃ¤ndigt att gÃ¶ra)