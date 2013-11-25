#include "SGS.h"
#include "Network.h"
#include "SDL/SDL_thread.h"
#include "Timer.h"
#include "StringInput.h"
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <fstream>
#include <vector>


using namespace Object;


void Menu::run()
{
  StringInput* inp = new StringInput;
  std::string name = "client1";
  SDL_Thread* thread = NULL;
  bool quit = false;
  Timer network_timer;
  Network* net = new Network();
  //
	m.play();
	Uint8 *keystates = SDL_GetKeyState(nullptr);
	std::string command;
	
	while(running) //medans programmet kÃ¶rs
	{
	  network_timer.start();
		while( SDL_PollEvent( &event)) //sÃ¥ lÃ¤nge som det finns en event
		{
		  // inp->handleInput(event);
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
				
				//run_command(command);
			}
			
			if( event.type == SDL_QUIT)    		// om krysset uppe till hÃ¶ger blev intryckt
			  running = false;      		    //
			if(keystates[SDLK_LALT] &&			// eller om alt + f4 blev intryckt
			   event.key.keysym.sym == SDLK_F4) //
			   running = false;// avsluta programmet
			if(event.type == SDL_KEYDOWN)
			  {
			    // inp->handleInput(event);
			    if(event.key.keysym.sym == SDLK_RETURN)
			      {
				net->sendChat(inp->getStr());
				inp->clear();
			      }
			    if(event.key.keysym.sym == SDLK_1)
			      {
				net->sendChat("join");
			      }
			    if(event.key.keysym.sym == SDLK_2)
			      {
				net->sendChat("en jätte glad client!!");
			      }
			    if(event.key.keysym.sym == SDLK_5)
			      {
				net->getChat();
				std::string tmp_str = "";
				tmp_str += net->getLog().at(0).first;
				tmp_str += "   |   ";
				tmp_str += net->getLog().at(0).second;
				dynamic_cast<Textbox*>(all_objects.at(0)) -> setText(tmp_str);
			      }
			    if(event.key.keysym.sym == SDLK_6)
			      {
				net->getChat();
				std::string tmp_str = "";
				tmp_str += net->getLog().at(1).first;
				tmp_str += "   |   ";
				tmp_str += net->getLog().at(1).second;
				dynamic_cast<Textbox*>(all_objects.at(0)) -> setText(tmp_str);
			      }
			    if(event.key.keysym.sym == SDLK_p)
			      {
				net->showMeDasLog();
			      }
			  }
		}
		
		
		net->getChat();
		std::string tmp_str = "";
		for(auto i : net->getLog())
		  {
		    tmp_str += i.first;
		    tmp_str += "   |   ";
		    tmp_str += i.second;
		    tmp_str += "<\n> " ;
		    
		  }
		dynamic_cast<Textbox*>(all_objects.at(0)) -> setText(tmp_str);

		paint();
		inp->showCentered(screen);
		SDL_Flip(screen);  
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
	writeSettings(settings);
	while(!all_objects.empty())
	{
		delete all_objects.back();
		all_objects.pop_back();
	}
	cleanUp({background});
	}
	catch(...)
	{
		return false;
	}

	return true;
}
void Menu::paint()
{

	applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	{
		all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	}
                 // Skriv ut bilden pÃ¥ skÃ¤rmen
}

#include "menu_commands.cpp" //enbart fÃ¶r att separera upp alla commands till en annan cpp fil, (detta Ã¤r ej nÃ¶dvÃ¤ndigt att gÃ¶ra)
