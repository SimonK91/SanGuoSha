#include "game_state.h"

using namespace object;
void GameState::run()
{
	int a = 0;
	while(1)
	{
		while( SDL_PollEvent( &event))
		{
			arrow.update_coordinates(event);
			apply_surface(0,0,background,screen);
			for(int i = 0 ; i < all_objects.size() ; ++i)
			{
				if(static_cast<active_object*>(all_objects.at(i)) != nullptr)
				{
					std::string temp = static_cast<active_object*>(all_objects.at(i))->handle_event(event,arrow);
					if(temp != "")
					{
						if(temp == "exit")
						{
							return;
						}
						else if(temp == "make_new_game")
						{
							make_button("test",50,50,"");
						}
						else if(temp == "")
						{
						
						}
						else if(temp == "")
						{
						
						}
					}
				}
				(all_objects.at(i))->print(screen);
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

void GameState::make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command)
{
	button* temp = new button(name, x_pos, y_pos, command);
	
	all_objects.push_back(temp);
}
/*
void GameState::make_button(const std::string& filename, const int& x_pos, const int& y_pos, const int& w_pos, const int& h_pos)
{
	all_objects.push_back() = new button{filename,x_pos,y_pos,w_pos,h_pos);
}*/
