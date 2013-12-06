void Game::run_command(const std::string& what_command)
{
	static int targetDodgeing = 0;
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
		for(int i = hand.size() -1 ; i >= 0 ; --i)
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
		std::vector<GameCard*> hand = target_player.at(targetDodgeing) -> getHand();
		GameCard* card = nullptr;
		
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "dodge")
			{
				card = target_player.at(targetDodgeing) -> playCard(i);
				break;
			}
		}
		
		if(card == nullptr)
			target_player.at(targetDodgeing) -> modifyLife(-1);
		else
			discard_pile -> pushBottom(card);
		
		target_player.at(targetDodgeing) -> setCurrentPlayer(false);
		targetDodgeing += 1;
		
		if(target_player.size() == targetDodgeing)
		{
			targetDodgeing = 0;
			current_player -> setCurrentPlayer(true);
			run_command("close_window");
		}	
		else
			target_player.at(targetDodgeing) -> setCurrentPlayer(true);
	}
	else if(what_command == "take_damage")
	{
		target_player.at(targetDodgeing) -> modifyLife(-1);
		target_player.at(targetDodgeing) -> setCurrentPlayer(false);
		
		targetDodgeing += 1;
		
		if(target_player.size() == targetDodgeing)
		{
			targetDodgeing = 0;
			current_player -> setCurrentPlayer(true);
			run_command("close_window");
		}	
		else
			target_player.at(targetDodgeing) -> setCurrentPlayer(true);
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
				if(i < target_player.at(0) -> getHandSize())
					current_player -> recieveCard( target_player.at(0) -> loseCard(i));
				else
				{
					//equipment
					GameCard* gc = dynamic_cast<GameCard*>(card);
					if((gc -> getAbility()).substr(0,6) == "weapon")
					{
						current_player -> recieveCard(target_player.at(0) -> loseEquipment(2));
					}
					else if((gc -> getAbility()).substr(0,6) == "shield")
					{
						current_player -> recieveCard(target_player.at(0) -> loseEquipment(3));
					}
					else if(gc -> getAbility() == "off_horse")
					{
						current_player -> recieveCard(target_player.at(0) -> loseEquipment(1));
					}	
					else if(gc -> getAbility() == "def_horse")
					{
						current_player -> recieveCard(target_player.at(0) -> loseEquipment(0));
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
		
		target_player.clear();
		run_command("close_window");
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
					if(i < target_player.at(0) -> getHandSize())
						discard_pile -> pushBottom(target_player.at(0) -> loseCard(i));
					else
					{
						//equipment
						GameCard* gc = dynamic_cast<GameCard*>(card);
						if((gc -> getAbility()).substr(0,6) == "weapon")
						{
							discard_pile -> pushBottom(target_player.at(0) -> loseEquipment(2));
						}
						else if((gc -> getAbility()).substr(0,6) == "shield")
						{
							discard_pile -> pushBottom(target_player.at(0) -> loseEquipment(3));
						}
						else if(gc -> getAbility() == "off_horse")
						{
							discard_pile -> pushBottom(target_player.at(0) -> loseEquipment(1));
						}	
						else if(gc -> getAbility() == "def_horse")
						{
							discard_pile -> pushBottom(target_player.at(0) -> loseEquipment(0));
						}
					}
				}
			}
		}
		//delete dummys
		while(dynamic_cast<HeroCard*>(dismantleWindow -> getObject(0)) != nullptr)
			delete dismantleWindow -> remove(0);
		
		//delete button
		delete dismantleWindow -> remove(dismantleWindow -> getSize()-1);
		
		//ta bort resten av pekarna
		while(dismantleWindow -> getSize() != 0)
			dismantleWindow -> remove(0);
		
		target_player.clear();
		run_command("close_window");
	}
	else if(what_command == "barbarian_attack")
	{
		static int barbarianTarget = 0;

		bool playedAttack = false;
		std::vector<GameCard*> hand = target_player.at(barbarianTarget) -> getHand();
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "attack")
			{
				playedAttack = true;
				discard_pile -> pushBottom(target_player.at(barbarianTarget) -> playCard(i));
				break; //so no more attackcards will be played
			}
		}
		
		if(!playedAttack)
			target_player.at(barbarianTarget) -> modifyLife(-1);
		
		//nästa spelare (devil)(huehuehue)
		target_player.at(barbarianTarget) -> setCurrentPlayer(false);
		barbarianTarget += 1;

		if(barbarianTarget == target_player.size())
		{
			barbarianTarget = 0;
			//döda fönstrett!!
			run_command("close_window");
			
			current_player -> setCurrentPlayer(true);
			target_player.clear();
		}
		else
			target_player.at(barbarianTarget) -> setCurrentPlayer(true);
	}
	else if(what_command == "arrow_attack")	
	{		
		static int arrowTarget = 0;

		bool playedDodge = false;
		std::vector<GameCard*> hand = target_player.at(arrowTarget) -> getHand();
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "attack")
			{
				playedDodge = true;
				discard_pile -> pushBottom(target_player.at(arrowTarget) -> loseCard(i));
				break;
			}
		}
		
		if(!playedDodge)
			target_player.at(arrowTarget) -> modifyLife(-1);
		
		//nästa spelare (devil)(huehuehue)
		target_player.at(arrowTarget) -> setCurrentPlayer(false);
		arrowTarget += 1;

		if(arrowTarget == target_player.size())
		{
			arrowTarget = 0;
			//döda fönstrett!!
			run_command("close_window");
			
			current_player -> setCurrentPlayer(true);
			target_player.clear();
		}
		else
			target_player.at(arrowTarget) -> setCurrentPlayer(true);
	}
	else if(what_command == "pick_card")
	{
		static int harvestTarget = 0;

		//hämta fönster
		Window* harvestWindow = dynamic_cast<Window*>(all_objects.back());
		
		//kolla om något valt
		GameCard* card = nullptr;
		int index = -1;
		for(unsigned i = 0; i < harvestWindow -> getSize() - 1; ++i)
		{
			card = dynamic_cast<GameCard*>(harvestWindow -> getObject(i));
			if(card != nullptr && card -> isActive())	
			{
				index = i;		//card is found and stored	
				break;
			}
		}
		
		//picka kort
		if(index != -1)
		{
			card -> setActive(false);
			target_player.at(harvestTarget) -> recieveCard(card);
			harvestWindow -> remove(index);
		}
		else if(harvestWindow -> getSize() != 1)
			return;	//inget kort valt!
			
		//byt spelare
		target_player.at(harvestTarget) -> setCurrentPlayer(false);
		harvestTarget = (harvestTarget + 1) % players.size();
		
		//om sig själv destruera fönstrett
		if(harvestWindow -> getSize() == 1)
		{
			harvestTarget = 0;
			
			run_command("close_window");
			//for the lulz			
			current_player -> setCurrentPlayer(true);
			target_player.clear();
		}
		else
			target_player.at(harvestTarget) -> setCurrentPlayer(true);
				
	}
	else if(what_command == "duel_attack")
	{
		static bool targetAttacking = true;
		int hasAttack = -1;
		std::vector<GameCard*> hand;
		//kollar om han har en attack
		if(targetAttacking)
			hand = target_player.at(0) -> getHand();
		else
			hand = current_player -> getHand();
			
		for(unsigned i = 0; i < hand.size(); ++i)
			if(hand.at(i) -> getAbility() == "attack")
				hasAttack = i;
				
		if(hasAttack != -1)
			if(targetAttacking)
				discard_pile -> pushBottom(target_player.at(0) -> playCard(hasAttack));
			else
				discard_pile -> pushBottom(current_player -> playCard(hasAttack));
		else
		{
			current_player -> setCurrentPlayer(true);
			target_player.at(0) -> setCurrentPlayer(false);
			if(targetAttacking)
				target_player.at(0) -> modifyLife(-1);
			else
				current_player -> modifyLife(-1);
				
			targetAttacking = true;
			//clean up
			run_command("close_window");
			return;
		}
		targetAttacking = !targetAttacking;

		target_player.at(0) -> setCurrentPlayer(targetAttacking);
		current_player -> setCurrentPlayer(!targetAttacking);
	}
	else if(what_command == "give_weapon")
	{
		//döda inte :( 
		if(current_player -> equipment.weapon != nullptr)
			discard_pile -> pushBottom(current_player -> loseEquipment(2));
		std::swap(current_player -> equipment.weapon,target_player.at(0) -> equipment.weapon);
		
		run_command("close_window");
		// target_player.clear();
	}
	else if(what_command == "duress_attack_respons")
	{
		std::vector<GameCard*> hand = target_player.at(0) -> getHand();
		int index = -1;
		for(unsigned i = 0; i < hand.size(); ++i)
			if(hand.at(i) -> getAbility() == "attack")
				index = i;
		
		
		if(index == -1)
		{
			//he was lying!
			run_command("give_weapon");
			target_player.at(0) -> setCurrentPlayer(false);
			current_player -> setCurrentPlayer(true);
			target_player.clear();
		}
		else
		{	
			GameCard* card = target_player.at(0) -> playCard(index);
			//swap players
			target_player.at(0) -> setCurrentPlayer(false);
			target_player.at(0) = target_player.at(1);
			target_player.pop_back();
			target_player.at(0) -> setCurrentPlayer(true);

			//ta bort duress fönstrett
			run_command("close_window");
			
			run_effect(card);
		
			discard_pile -> pushBottom(card);
		}
	}
	else
	{
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
	}
	return;
}

