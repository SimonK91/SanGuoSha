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
	  if(timer->checkStarted() == true)
	    {
	      timer->stop();
	    }
	  timer->start(5);
	  timer->setCommand("end_turn");
	  std::cout << "Ny timer med end turn 5 sek" << std::endl;
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
		for(unsigned i = 0; i < players.size(); ++i)
		{
			if(current_player == players.at(i))
			{
				self = i;
			}
		}
		
		std::vector<GameCard*> hand = target_player -> getHand();
		GameCard* card = nullptr;
		
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			if(hand.at(i) -> getAbility() == "dodge")
			{
				card = target_player -> playCard(i);
				break;
			}
		}
		
		if(card == nullptr)
			target_player -> modifyLife(-1);
		else
			discard_pile -> pushBottom(card);
		
		target_player -> setCurrentPlayer(false);
		target_player = nullptr;
		current_player -> setCurrentPlayer(true);

		run_command("close_window");
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
		run_command("close_window");
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
		
		target_player = nullptr;
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
		
		target_player = nullptr;
		run_command("close_window");
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
			run_command("close_window");
			
			current_player -> setCurrentPlayer(true);
			target_player = nullptr;
		}
	}
		else if(what_command == "arrow_attack")	
	{
		static int arrowTarget = -1;
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
			
			run_command("close_window");
			current_player -> setCurrentPlayer(true);
			target_player = nullptr;
		}
	}
	else if(what_command == "pick_card")
	{
		//fix index
		static int harvestTarget = -1;
		if(harvestTarget == -1)
			harvestTarget = self;
		//hämta fönster
		Window* harvestWindow = dynamic_cast<Window*>(all_objects.back());
		
		//kolla om något valt
		GameCard* card = nullptr;
		int index = -1;
		for(int i = 0; i < harvestWindow -> getSize() - 1; ++i)
		{
			card = dynamic_cast<GameCard*>(harvestWindow -> getObject(i));
			if(card -> isActive())	
			{
				index = i;
				break;				//card is found and stored
			}
			card = nullptr;
		}
		
		//picka kort
		if(card != nullptr)
		{
			card -> setActive(false);
			target_player -> recieveCard(card);
			harvestWindow -> remove(index);
		}
		else
			return;	//inget kort valt!
			
		//byt spelare
		target_player -> setCurrentPlayer(false);
		harvestTarget = (harvestTarget + 1) % players.size();
		target_player = players.at(harvestTarget);
		target_player -> setCurrentPlayer(true);
		
		//om sig själv destruera fönstrett
		if(harvestTarget == self)
		{
			harvestTarget = -1;
			
			run_command("close_window");
			//for the lulz			
			current_player -> setCurrentPlayer(true);
			target_player = nullptr;
		}
	}
	else if(what_command == "duel_attack")
	{
		static bool targetAttacking = true;
		int hasAttack = -1;
		std::vector<GameCard*> hand;
		//kollar om han har en attack
		if(targetAttacking)
			hand = target_player -> getHand();
		else
			hand = current_player -> getHand();
			
		for(int i = 0; i < hand.size(); ++i)
			if(hand.at(i) -> getAbility() == "attack")
				hasAttack = i;
				
		if(hasAttack != -1)
			if(targetAttacking)
				discard_pile -> pushBottom(target_player -> playCard(hasAttack));
			else
				discard_pile -> pushBottom(current_player -> playCard(hasAttack));
		else
		{
			current_player -> setCurrentPlayer(true);
			target_player -> setCurrentPlayer(false);
			if(targetAttacking)
				target_player -> modifyLife(-1);
			else
				current_player -> modifyLife(-1);
				
			targetAttacking = true;
			//clean up
			run_command("close_window");
			return;
		}
		targetAttacking = !targetAttacking;

		target_player -> setCurrentPlayer(targetAttacking);
		current_player -> setCurrentPlayer(!targetAttacking);
	}
	else if(what_command == "duress_attack")
	{
		if(target_player != nullptr)
		{
			current_player -> setCurrentPlayer(false);
			source_player -> setCurrentPlayer(true);
			
			//ta bort duress_attack knappen
			delete all_objects.back();
			all_objects.pop_back();
			//skapa ett fönster med val
			Window* duressWindow = new Window(160,250,500,250);
			duressWindow -> makeTextbox(40,40,420,30);
			duressWindow -> setText(0,"Attack " + current_player -> getHeroName()  + " or lose your weapon to " + current_player -> getHeroName());
			
			duressWindow -> makeButton("Attack",37,170,"duress_attack_respons");
			duressWindow -> makeButton("Give weapon",260,170,"give_weapon");
			has_window = true;
			add_window(duressWindow);
		}
	}
	else if(what_command == "give_weapon")
	{
		//döda inte :( 
		if(current_player -> equipment.weapon != nullptr)
			discard_pile -> pushBottom(current_player -> loseEquipment(2));
		std::swap(current_player -> equipment.weapon,source_player -> equipment.weapon);
		
		run_command("close_window");
		source_player = nullptr;
		target_player = nullptr;
	}
	else if(what_command == "duress_attack_respons")
	{
		std::vector<GameCard*> hand = source_player -> getHand();
		int index = -1;
		for(int i = 0; i < hand.size(); ++i)
			if(hand.at(i) -> getAbility() == "attack")
				index = i;
		
		
		if(index == -1)
		{
			//he was lying!
			run_command("give_weapon");
		}
		else
		{	
			GameCard* card = source_player -> playCard(index);
			source_player -> setCurrentPlayer(false);
			target_player -> setCurrentPlayer(true);

			//ta bort duress fönstrett
			run_command("close_window");
			
			run_effect(card);
		
			discard_pile -> pushBottom(card);
			// target_player -> setCurrentPlayer(false);
			// current_player -> setCurrentPlayer(true);
		}
	}
	else
	{
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
	}
	return;
}

