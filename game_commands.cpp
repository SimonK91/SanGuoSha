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
		hand = current_player -> getHand();
		for(unsigned i = 0; i < hand.size() ; ++i)
		{
			if(hand.at(i) -> isActive())
			{
				GameCard* card = current_player -> playCard(i);
				std::cout << "Card played: " << card -> getAbility() << std::endl;
				card = run_effect(card);
				if(card != nullptr)
				{
					std::cout << "Played card: " + card -> getAbility() + " was plased in discard pile" << std::endl;
					card -> setActive(false);
					discard_pile -> pushBottom(card);
				}
				break; //safty if 2 cards is active!
			}
		}
		current_player -> setSelected(false);
	}
	else if(what_command == "discard_card")
	{
		std::vector<GameCard*> hand;
		hand = current_player -> getHand();
		for(unsigned i = hand.size() -1 ; i >= 0 ; --i)
		{
			if(hand.at(i) -> isActive())
			{
				GameCard* card = current_player -> loseCard(i);
				card -> setActive(false);
				discard_pile -> pushBottom(card);
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
		has_window = false;
		// std::cout << "dodge done!" << std::endl;
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
		
		has_window = false;
		target_player = nullptr;
		delete all_objects.back();
		all_objects.pop_back();
	}
	else if(what_command == "steal_card")
	{
		Window* stealWindow = dynamic_cast<Window*>(all_objects.back());
		Card* card;
		
		for(unsigned i = 0 ; i < stealWindow->getSize() ; ++i)
		{
			card = dynamic_cast<Card*>(stealWindow -> getObject(i));
			if(card != nullptr && card -> isActive())
			{
			// hittat rätt kort som ska stjälas
				if(i < target_player -> getHandSize())
					current_player -> recieveCard( target_player -> loseCard(i));
				else
				{
					//equipment
					GameCard* gc = dynamic_cast<GameCard*>(card);
					if((gc -> getAbility()).substr(0,6) == "weapon")
					{
						current_player -> recieveCard(target_player -> loseEquipment(2));
					}
					else if((gc -> getAbility()).substr(0,6) == "shield")
					{
						current_player -> recieveCard(target_player -> loseEquipment(3));
					}
					else if(gc -> getAbility() == "off_horse")
					{
						current_player -> recieveCard(target_player -> loseEquipment(1));
					}	
					else if(gc -> getAbility() == "def_horse")
					{
						current_player -> recieveCard(target_player -> loseEquipment(0));
					}
				}
			}
		}
		//delete dummys
		while(dynamic_cast<HeroCard*>(stealWindow -> getObject(0)) != nullptr)
		{
			delete stealWindow -> remove(0);
		}
		//delete button
		delete dynamic_cast<Button*> (stealWindow -> remove(stealWindow -> getSize()-1));
		
		while(stealWindow -> getSize() != 0)
			stealWindow -> remove(0);
		
		has_window = false;
		target_player = nullptr;
		
		delete all_objects.back();
		all_objects.pop_back();
	}
	else if(what_command == "dismantle_card")
	{
		Window* dismantleWindow = dynamic_cast<Window*>(all_objects.back());
		Card* card;
		
		for(unsigned i = 0 ; i < dismantleWindow->getSize() ; ++i)
		{
			card = dynamic_cast<Card*>(dismantleWindow -> getObject(i));
			if(card != nullptr && card -> isActive())
			{
				card = dynamic_cast<Card*>(dismantleWindow -> getObject(i));
				if(card != nullptr && card -> isActive())
				{
				// hittat rätt kort som ska stjälas
					if(i < target_player -> getHandSize())
						discard_pile -> pushBottom(target_player -> loseCard(i));
					else
					{
						//equipment
						GameCard* gc = dynamic_cast<GameCard*>(card);
						if((gc -> getAbility()).substr(0,6) == "weapon")
						{
							discard_pile -> pushBottom(target_player -> loseEquipment(2));
						}
						else if((gc -> getAbility()).substr(0,6) == "shield")
						{
							discard_pile -> pushBottom(target_player -> loseEquipment(3));
						}
						else if(gc -> getAbility() == "off_horse")
						{
							discard_pile -> pushBottom(target_player -> loseEquipment(1));
						}	
						else if(gc -> getAbility() == "def_horse")
						{
							discard_pile -> pushBottom(target_player -> loseEquipment(0));
						}
					}
				}
			}
		}
		//delete dummys
		while(dynamic_cast<HeroCard*>(dismantleWindow -> getObject(0)) != nullptr){
			delete dismantleWindow -> getObject(0);
			dismantleWindow -> remove(0);
		}
		//delete button
		delete dismantleWindow -> remove(dismantleWindow -> getSize()-1);
		
		while(dismantleWindow -> getSize() != 0)
			dismantleWindow -> remove(0);
		
		has_window = false;
		target_player = nullptr;
		
		delete all_objects.back();
		all_objects.pop_back();
	}
	else if(what_command == "barbarian_attack")	//ej klar
	{
		static int barbarianTarget = -1;//problem kanske fixat
		if(barbarianTarget == -1)
		{
			barbarianTarget = (self + 1) % players.size();
		}
		bool playedAttack = false;
		std::vector<GameCard*> hand = target_player -> getHand();
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "attack")
			{
				playedAttack = true;
				discard_pile -> pushBottom(target_player -> loseCard(i));
				break;
			}
		}
		
		if(!playedAttack)
			target_player -> modifyLife(-1);
		
		//nästa spelare (devil)(huehuehue)
		barbarianTarget = (barbarianTarget+1) % players.size();
		target_player -> setCurrentPlayer(false);
		target_player = players.at(barbarianTarget);
		target_player -> setCurrentPlayer(true);
		
		if(barbarianTarget == self)
		{
			barbarianTarget = -1;
			//döda fönstrett!!
			has_window = false;
			delete all_objects.back();
			all_objects.pop_back();
			
			current_player -> setCurrentPlayer(true);
			target_player = nullptr;
		}
	}
		else if(what_command == "arrow_attack")	//ej klar
	{
		static int arrowTarget = -1;//problem kanske fixat
		if(arrowTarget == -1)
		{
			arrowTarget = (self + 1) % players.size();
		}
		bool playedDodge = false;
		std::vector<GameCard*> hand = target_player -> getHand();
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "dodge")
			{
				playedDodge = true;
				discard_pile -> pushBottom(target_player -> loseCard(i));
				break;
			}
		}
		
		if(!playedDodge)
			target_player -> modifyLife(-1);
		
		//nästa spelare (devil)(huehuehue)
		arrowTarget = (arrowTarget+1) % players.size();
		target_player -> setCurrentPlayer(false);
		target_player = players.at(arrowTarget);
		target_player -> setCurrentPlayer(true);
		
		if(arrowTarget == self)
		{
			arrowTarget = -1;
			//döda fönstrett!!
			has_window = false;
			delete all_objects.back();
			all_objects.pop_back();
			
			current_player -> setCurrentPlayer(true);
			target_player = nullptr;
		}
	}
	else
	{
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
	}
	return;
}

