#include "game_state.h"

using namespace object;
void GameState::run()
{
	while(1)
	{
		while( SDL_PollEvent( &event))
		{
			arrow.update_coordinates(event);
			apply_surface(0,0,background,screen);
			for(auto it = all_objects.begin() ; it != all_objects.end() ; ++it)
			{
				if(static_cast<active_object*>(*it) != nullptr)
					static_cast<active_object*>(*it)->handle_event(event,arrow);
				(*it)->print(screen);
			}
			if( event.type == SDL_QUIT )
			{
				return;
			}
		}
	
	SDL_Flip(screen);
	SDL_Delay(15);
	}
}

void GameState::make_button(const std::string& filename, const int& x_pos, const int& y_pos, const int& w_pos, const int& h_pos)
{
	button* temp = new button(filename,x_pos,y_pos,w_pos,h_pos);
	
	all_objects.push_back(temp);
}
/*
void GameState::make_button(const std::string& filename, const int& x_pos, const int& y_pos, const int& w_pos, const int& h_pos)
{
	all_objects.push_back() = new button{filename,x_pos,y_pos,w_pos,h_pos);
}*/
