void Game::run_command(const std::string& what_command)
{
	if(what_command == "")
		return;
		
	
	if(what_command == "close")
	{
		running = false;
		return;
	}
	if(what_command == "pick_hero")
	{
		Window* hero_window = dynamic_cast<Window*>(all_objects.back());
		HeroCard* hero;
		for(unsigned i = 0 ; i < hero_window->getSize() ; ++i)
		{
			hero = dynamic_cast<HeroCard*>(hero_window->getObject(i));
			if(hero!=nullptr)
			{
				std::cout << "hero " << i << std::endl;
				if(hero->isActive())
				{
					std::cout << "HERO " << i << " active" << std::endl;
					//ge dig själv hero-kortet
					players.at(self)->setHero(hero);
					std::cout << "ger kortet" << std::endl;
				
					//tar bort kortet från window
					hero_window->remove(i);
					
					//för varje annat objekt i fönstret
					for(unsigned j = 0 ; j < hero_window->getSize() ; ++j)
					{
						std::cout << "för objekt " << j << ":" << std::endl;
						//om det är ett heroCard, flytta in det i hero deck
						if(dynamic_cast<HeroCard*>(hero_window->getObject(j)) != nullptr)
						{
							std::cout << "dynamic cast success" << std::endl;
							hero_deck->pushBottom(dynamic_cast<HeroCard*>(hero_window->getObject(j)));
						}
						//annars ta bort det
						else
						{
							std::cout << "normal delete" << std::endl;
							delete hero_window->getObject(j);
						}
						//sätt positionen till nullptr
						//hero_window->getObject(j) = nullptr;
					}
					//ta bort fönstret
					all_objects.pop_back();
					i = hero_window->getSize();
				}
			}			
		}
	}
	if(what_command == "options")
	{
		Window* options = new Window(160,50,500,450);
		options->makeButton("Fullscreen",30,20,"toggle_fullscreen");
		options->makeButton("Back",270,390,"close_window");
		//options->makeTextbox(("Music volume: " + I2S(m.getVolume())),300,20,150,30);
		options->makeSlider(250,60,"set_volume",m.getVolume());
		add_window(options);
		has_window = true;
	}
	if(what_command == "close_window")
	{
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	if(what_command.substr(0,10) == "set_volume")
	{
		//hitta grejer3
		int volume = S2I(what_command.substr(11,what_command.size()-11));
		m.setVolume(volume);
		//settings.at(1).second = I2S(volume);
		dynamic_cast<Window*>(all_objects.back())->setText(2,"Music volume: " +  I2S(m.getVolume()));
	}
	if(what_command == "toggle_fullscreen")
	{
		if(!fullscreen)
		{
			screen = SDL_SetVideoMode(800,600,32, screen->flags+SDL_FULLSCREEN);
			fullscreen = true;
			//settings.at(2).second = "on";
		}
		else
		{
			screen = SDL_SetVideoMode(800,600,32, screen->flags-SDL_FULLSCREEN);
			fullscreen = false;
			//settings.at(2).second = "off";
		}
	}


	if(what_command == "set_settings")
	  {
	    
	    //toggle sounds not yet implementet

	    //set volume
		if(settings.size() > 2)
		{
	     int volume = S2I(settings.at(1).second);
	    m.setVolume(volume);
	    //fullscreen on/off
	    if(settings.at(2).second == "on")
	      {
		screen = SDL_SetVideoMode(800,600,32, screen->flags+SDL_FULLSCREEN);
		fullscreen = true;
	      }
	    else
	      {
		//screen = SDL_SetVideoMode(800,600,32, screen->flags-SDL_FULLSCREEN);
		fullscreen = false;
	      }
		}
		else
		{
			m.setVolume(67);
			fullscreen = false;
		}
	  }
	return;
}
