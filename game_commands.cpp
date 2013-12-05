void Game::run_command(const std::string& what_command)
{
	if(what_command == "")
		return;
		
	
	else if(what_command == "close")
	{
		running = false;
		return;
	}
	else if(what_command == "next_state")
	{
		all_objects.pop_back();
		++state;
		has_window = false;
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
					while(hero_window->getSize() != 0)
					{
						//om det är ett heroCard, flytta in det i hero deck
						if(dynamic_cast<HeroCard*>(hero_window->getObject(0)) != nullptr)
						{
							std::cout << "dynamic cast success" << std::endl;
							hero_deck->pushBottom(dynamic_cast<HeroCard*>(hero_window->remove(0)));
							
						}
						//annars ta bort det
						else
						{
							std::cout << "normal delete" << std::endl;
							delete hero_window->remove(0);
						}
					}
					//ta bort fönstret
					delete all_objects.back();
					all_objects.pop_back();
					i = hero_window->getSize();
					has_window = false;
				}
			}			
		}
	}
	else if(what_command == "close_window")
	{
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	
	else if(what_command == "end_turn")
	{
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
	else if(what_command == "dodge")
	{
		// std::cout << "dodge begin" << std::endl;
		for(unsigned i = 0; i < players.size(); ++i)
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
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "dodge")
			{
				card = target_player -> playCard(i);
				break;
			}
		}
		
		if(card == nullptr)
		{
			target_player -> modifyLife(-1);
		}
		else
		{
			discard_pile -> pushBottom(card);
		}
		
		// std::cout << "fixed discard_pile" << std::endl;
		
		target_player -> setCurrentPlayer(false);
		target_player = nullptr;
		current_player -> setCurrentPlayer(true);

		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	else if(what_command == "take_damage")
	{
		for(unsigned i = 0; i < players.size(); ++i)
		{
			if(current_player == players.at(i))
			{
				self = i;
			}
		}
		target_player -> modifyLife(-1);
		
		target_player -> setCurrentPlayer(false);
		
		current_player -> setCurrentPlayer(true);
		
		target_player = nullptr;
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	else
	{
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
	}
	return;
}

