#include "game_state.h"

using namespace object;

//Destruktor
GameState::~GameState(){} //destruering sker i slutet av run!


//Mainfunktionen i GameState
void GameState::run()
{
	m.play();
	while(running) //medans programmet körs
	{
		while( SDL_PollEvent( &event)) //så länge som det finns en event
		{
			arrow.update_coordinates(event); //uppdatera position för musen
			apply_surface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
			
			for(unsigned i = 0 ; i < all_objects.size() ; ++i)  //för varje objekt som finns i gamestatet
			{
				
				if(dynamic_cast<active_object*>(all_objects.at(i)) != nullptr && !has_window) //om objektet är ett aktivt objekt (aktiva objekt kan manipulera saker)
				{
					std::string command = dynamic_cast<active_object*>(all_objects.at(i))->handle_event(event,arrow); //kör handle event på objektet (detta ser om kriterier är uppfyllda för att göra något
					if(command != "") //om man fick tillbaka annat än en tom sträng
					{
						run_command(command,i); //kör kommandot för denna sträng
						
					}	
				}
				else if(dynamic_cast<window*>(all_objects.at(i)) != nullptr)
				{
					std::string command = dynamic_cast<window*>(all_objects.at(i))->handle_event(event,arrow); //kör handle event på objektet (detta ser om kriterier är uppfyllda för att göra något
					if(command != "") //om man fick tillbaka annat än en tom sträng
					{
						run_command(command,i); //kör kommandot för denna sträng
						//rensa events 
						//gör det senare så får vi mindre lagg :D
						
						break;
					}
				}
				if(i < all_objects.size())
				{
					all_objects.at(i)->print(screen); // för varje objekt (oavsett aktivt eller inte), skriv ut det på skärmen
				}
			}
			if( event.type == SDL_QUIT )    // om krysset uppe till höger blev intryckt
			{
				running = false;            // avsluta GameStatet
			}
		}
		SDL_Flip(screen);                   // Skriv ut bilden på skärmen
		SDL_Delay(15);                      // Vänta 15ms för att sänka fps lite
	}
	
	while(!all_objects.empty())
	{
		delete all_objects.back();
		all_objects.pop_back();
	}
	clean_up({background});
}



//för att skapa alla objekttyper
bool GameState::make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command,
							const std::string& image, const unsigned& size)
{
	button* temp = new button(name, x_pos, y_pos, command, image, size);
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}
bool GameState::make_slider(const int& x_pos, const int& y_pos, const std::string& command)
{
	slider* temp = new slider(x_pos, y_pos, command,m.getVolume());
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}

bool GameState::make_textbox(const std::string& text, const int& x, const int& y, const int& w , const int& h
							,const SDL_Color &col, const std::string& font, const unsigned& size)
{
	text_box* temp = new text_box(text,x,y,w,h,col,font,size);
	
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	//all_objects.pop_back();
	return true;
	
}
bool GameState::add_window(object::window* your_window)
{
	if(your_window == nullptr)
		return false;
	all_objects.push_back(your_window);
	return true;
}

#include "game_state_commands.cpp" //enbart för att separera upp alla commands till en annan cpp fil, (detta är ej nödvändigt att göra)