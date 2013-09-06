#include "game_state.h"

using namespace object;

//Destruktor
GameState::~GameState()
{
	clean_up({background}); //screen är utifrån och tas bort där, ta inte bort den här, då kraschar programmet!
	for(auto it : all_objects)
	{
		delete it;          //varje objekt tas bort så att man undviker minnesläckor
	}
}


//Mainfunktionen i GameState
void GameState::run()
{
	while(running) //medans programmet körs
	{
		while( SDL_PollEvent( &event)) //så länge som det finns en event
		{
			arrow.update_coordinates(event); //uppdatera position för musen
			apply_surface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
			
			for(unsigned i = 0 ; i < all_objects.size() ; ++i)  //för varje objekt som finns i gamestatet
			{
				if(static_cast<active_object*>(all_objects.at(i)) != nullptr) //om objektet är ett aktivt objekt (aktiva objekt kan manipulera saker)
				{
					std::string command = static_cast<active_object*>(all_objects.at(i))->handle_event(event,arrow); //kör handle event på objektet (detta ser om kriterier är uppfyllda för att göra något
					if(command != "") //om man fick tillbaka annat än en tom sträng
					{
						run_command(command); //kör kommandot för denna sträng
					}	
				}
				
				all_objects.at(i)->print(screen); // för varje objekt (oavsett aktivt eller inte), skriv ut det på skärmen
			}
			if( event.type == SDL_QUIT )    // om krysset uppe till höger blev intryckt
			{
				running = false;            // avsluta GameStatet
			}
		}
		SDL_Flip(screen);                   // Skriv ut bilden på skärmen
		SDL_Delay(15);                      // Vänta 15ms för att sänka fps lite
	}
}



//för att skapa alla objekttyper
bool GameState::make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command)
{
	button* temp = new button(name, x_pos, y_pos, command);
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}
bool GameState::make_slider(const int& x_pos, const int& y_pos, const std::string& command)
{
	slider* temp = new slider(x_pos, y_pos, command);
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}

bool GameState::make_textbox(const std::string& text, const int& x, const int& y, const int& w, const int& h ,SDL_Color col, const std::string& font, const int& size)
{
	/*
	text_box* temp = new text_box();
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
*/
	return false;
}

#include "game_state_commands.cpp" //enbart för att separera upp alla commands till en annan cpp fil, (detta är ej nödvändigt att göra)