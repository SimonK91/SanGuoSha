void Game::run_command(const std::string& what_command)
{
	if(what_command == "")
		return;
		
	
	else if(what_command == "close")
	{
		running = false;
		return;
	}
	else if(what_command == "pick_hero")
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
					}
					//ta bort fönstret
					all_objects.pop_back();
					i = hero_window->getSize();
				}
			}			
		}
	}
	else if(what_command == "options")
	{
		Window* options = new Window(160,50,500,450);
		options->makeButton("Fullscreen",30,20,"toggle_fullscreen");
		options->makeButton("Back",270,390,"close_window");
		//options->makeTextbox(("Music volume: " + I2S(m.getVolume())),300,20,150,30);
		options->makeSlider(250,60,"set_volume",m.getVolume());
		add_window(options);
		has_window = true;
	}
	else if(what_command == "close_window")
	{
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	else if(what_command.substr(0,10) == "set_volume")
	{
		//hitta grejer3
		int volume = S2I(what_command.substr(11,what_command.size()-11));
		m.setVolume(volume);
		//settings.at(1).second = I2S(volume);
		dynamic_cast<Window*>(all_objects.back())->setText(2,"Music volume: " +  I2S(m.getVolume()));
	}
	else if(what_command == "toggle_fullscreen")
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


	else if(what_command == "set_settings")
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
	else if(what_command == "end_turn")
	{ 
	  if(timer->checkStarted() == true)
	    {
	      timer->stop();
	    }
	  timer->start(5);
	  timer->setCommand("time_out");
	  std::cout << "Ny timer med time out 5 sek" << std::endl;
	  
	  state = 5;	//go to discard phase in game
	}
	else if(what_command == "play_card")
	{
		std::vector<GameCard*> hand;
		for(Player* p : players)
		{
			if(p -> isCurrentPlayer())
			{
				hand = p -> getHand();
				for(unsigned i = 0; i < hand.size() ; ++i)
				{
					if(hand.at(i) -> isActive())
					{
						GameCard* card = p -> playCard(i);
						card = run_effect(card);
						if(card != nullptr)
							discard_pile -> pushBottom(card);
						break; //safty if 2 cards is active!
					}
				}
			}
			p -> setSelected(false);
		}
		if(timer->checkStarted() == true)
		  {
		    timer->stop();
		  }
		timer->start(5);
		timer->setCommand("end_turn");
		std::cout << "Ny timer med time out 5 sek" << std::endl;
		
		
	}
	else if(what_command == "discard_card")
	{
	  std::vector<GameCard*> hand;
		for(Player* p : players)
		{
			if(p -> isCurrentPlayer())
			{
				hand = p -> getHand();
				for(unsigned i = 0; i < hand.size(); ++i)
				{
					if(hand.at(i) -> isActive())	//den är fel kommer aldrig hit!
					{
						GameCard* card = p -> loseCard(i);
						discard_pile -> pushBottom(card);
						break; //safty if 2 cards is active!
					}
				}
			}
		}
	}
	else if(what_command == "time_out")
	  {
	    std::cout << "discard phase time out" << std::endl;
	    while(players.at(self) -> getCurrentHP() < players.at(self) -> getHandSize())
	      {
		GameCard* card = players.at(self) -> loseCard( players.at(self)->getHandSize()-1);
		  discard_pile -> pushBottom(card);
	      }
	    state = 6;
	  }
	else if(what_command == "dodge")
	{
		// std::cout << "dodge begin" << std::endl;
		for(int i = 0; i < players.size(); ++i)
		{
			if(current_player == players.at(i))
			{
				self = i;
			}
		}
		
		// std::cout << "player fixed" << std::endl;
		std::vector<GameCard*> hand = target_player -> getHand();
		GameCard* card = nullptr;
		
		// std::cout << "target player used" << std::endl;
		for(int i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "dodge")
			{
				card = target_player -> playCard(i);
				break;
			}
		}
		
		// std::cout << "hand gone through" << std::endl;
		if(card == nullptr)
			target_player -> modifyLife(-1);
		else
			discard_pile -> pushBottom(card);
		
		
		// std::cout << "fixed discard_pile" << std::endl;
		
		target_player -> setCurrentPlayer(false);
		target_player = nullptr;
		current_player -> setCurrentPlayer(true);

		delete all_objects.back();
		all_objects.pop_back();
		// std::cout << "dodge done!" << std::endl;
	}
	else if(what_command == "take_damage")
	{
		for(int i = 0; i < players.size(); ++i)
		{
			if(current_player == players.at(i))
			{
				self = i;
			}
		}
		std::cout << "current hp: " << target_player -> getCurrentHP() << std::endl;
		target_player -> modifyLife(-1);
		
		std::cout << "current hp after mod: " << target_player -> getCurrentHP() << std::endl;
		target_player -> setCurrentPlayer(false);
		target_player = nullptr;
		
		current_player -> setCurrentPlayer(true);
		
		target_player = nullptr;
		delete all_objects.back();
		all_objects.pop_back();
	}
	else
	{
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
	}
	return;
}

