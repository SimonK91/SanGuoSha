GameCard* Game::run_effect(Object::GameCard* gameCard)
{
  GameCard* card = nullptr;
  std::string effect = gameCard -> getAbility();
  
  if(effect == "draw2" && !negated())
    {
      m.playSoundEffect(8);
      for(int i = 0; i < 2; ++i)
	{
	  if(card_deck -> empty())
	    {
	      std::swap(card_deck,discard_pile);
	      card_deck -> shuffle();
	    }		
	  card = dynamic_cast<GameCard*>(card_deck -> drawCard());
	  current_player -> recieveCard(card);
	}
    }
  else if(effect == "attack")	//måste fixas mera!!! sköldar + vapen o skit!
    {
	
		if(!useCard("dodge", "dodge the attack or lose a life",target_player.at(0)))
			target_player.at(0) ->modifyLife(-1);
    }
	
  else if(effect == "heal")
    {
		if(target_player.size() != 0 && target_player.at(0) -> getLife() <= 0)
		{
			target_player.at(0) -> modifyLife(1);
		}
		else
			current_player -> modifyLife(1);
    }
  else if(effect == "off_horse")
    {
      m.playSoundEffect(2);
      gameCard = current_player -> equipStuff(gameCard,3);
    }
  else if(effect == "def_horse")
    {
      m.playSoundEffect(2);
      gameCard = current_player -> equipStuff(gameCard,4);
    }
  else if(effect.substr(0,6) == "weapon")
    {
      m.playSoundEffect(1);
      gameCard = current_player -> equipStuff(gameCard,1);
    }
  else if(effect.substr(0,6) == "shield")
    {
      m.playSoundEffect(0);
      gameCard = current_player -> equipStuff(gameCard,2);
    }
  else if(effect == "peach_garden")
    {
		for(Player* p : players)
		{
			if(p->getLife() != p->getMaxLife() && !negated())
			{
				p -> modifyLife(1);
			}
		}
    }
  else if(effect == "acedia")
    {
		target_player.at(0) -> addJudgementCard(gameCard);
		gameCard = nullptr;
    }
  else if(effect == "lightning")
    {
   		current_player -> addJudgementCard(gameCard);
		gameCard = nullptr;
	}
  else if(effect == "steal" && !negated())
    {
     
	  timer->reset(sett.getTimerTime(),"steal_time_out");
	  state = 7;
	 
	 	Window* stealWindow = new Window(50,150,600,350);

		std::vector<GameCard*> targetHand = target_player.at(0) -> getHand();
			
		for(unsigned i = 0; i < targetHand.size(); ++i)
		{
			stealWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
		}
		//add equipment
		if(target_player.at(0) -> equipment.weapon != nullptr)
			stealWindow -> addCard(target_player.at(0) -> equipment.weapon,0, 240);
		if(target_player.at(0) -> equipment.shield != nullptr)
			stealWindow -> addCard(target_player.at(0) -> equipment.shield, 100, 240);
		if(target_player.at(0) -> equipment.off_horse != nullptr)
			stealWindow -> addCard(target_player.at(0) -> equipment.off_horse, 200, 240);
		if(target_player.at(0) -> equipment.def_horse != nullptr)
			stealWindow -> addCard(target_player.at(0) -> equipment.def_horse, 300, 240);
			
			
		stealWindow -> makeButton("Steal",170,250, "steal_card");
		add_window(stealWindow);
		has_window = true;
    }
  else if(effect == "dismantle" && !negated())
    {
	  state = 7;
	  timer->reset(sett.getTimerTime(), "dismantle_time_out");
	  
		Window* dismantleWindow = new Window(50,150,600,350);
		std::vector<GameCard*> targetHand = target_player.at(0) -> getHand();
		
		for(unsigned i = 0; i < targetHand.size(); ++i)
		{
			dismantleWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
		}
		//add equipment
		if(target_player.at(0) -> equipment.weapon != nullptr)
			dismantleWindow -> addCard(target_player.at(0) -> equipment.weapon,0, 240);
		if(target_player.at(0) -> equipment.shield != nullptr)
			dismantleWindow -> addCard(target_player.at(0) -> equipment.shield, 100, 240);
		if(target_player.at(0) -> equipment.off_horse != nullptr)
			dismantleWindow -> addCard(target_player.at(0) -> equipment.off_horse, 200, 240);
		if(target_player.at(0) -> equipment.def_horse != nullptr)
			dismantleWindow -> addCard(target_player.at(0) -> equipment.def_horse, 300, 240);
			
		dismantleWindow -> makeButton("dismantle",170,250, "dismantle_card");
		add_window(dismantleWindow);
		has_window = true;
	}
  else if(effect == "barbarian")
    {
      m.playSoundEffect(5);
      // timer->reset(sett.getTimerTime(),"barbarian_attack");
	  for(int nP = nextPlayer(); nP != (int)self ; nP = nextPlayer(nP))
			if(!useCard("attack","attack the barbarians or lose a life",players.at(nP)))
				players.at(nP) -> modifyLife(-1);
 		// Window* barbarianWindow = new Window(50,350,350,200);
		
		// // barbarianWindow -> addCard(gameCard,400,350);
		// barbarianWindow -> makeTextbox(20,40,310,30);
		// barbarianWindow -> makeButton("Attack!!!",70,100,"barbarian_attack");
		// barbarianWindow -> setText(0,"   Attack the barbarians or lose a life!");
		// add_window(barbarianWindow);
		// has_window = true;
		
		// //current player is going to go around
		// current_player -> setCurrentPlayer(false);
		// target_player.clear();
		// for(int i = (self + 1) % players.size(); i != self; i = (i + 1) % players.size())
			// target_player.push_back(players.at(i));
		
		// // target_player.at(0) = players.at((self +1) % players.size());
		// target_player.at(0) -> setCurrentPlayer(true);
    }
  else if(effect == "raining_arrows")
    {
      m.playSoundEffect(6);
	  for(int nP = nextPlayer(); nP != (int)self ; nP = nextPlayer(nP))
			if(!negated("negate barbarian for " + players.at(nP) ->getName()) && !useCard("dodge","dodge the rain of arrows or lose a life",players.at(nP)))
				players.at(nP) -> modifyLife(-1);
				
    }
  else if(effect == "harvest")
    {
		harvest();
    }
  else if(effect == "duel" && !negated())
    {
		Player* defender = target_player.at(0);
		Player* offender = current_player;
		int CP = 0;
		bool attacked = false;
		do
		{
			if(CP%2 == 0)
				attacked = useCard("attack","You are dueled, use attack or lose a life",defender);
			else
				attacked = useCard("attack","You are dueled, use attack or lose a life",offender);
				
			++CP;
		}while(attacked);
		
		if(CP%2 == 1)
			defender -> modifyLife(-1);
		else
			offender -> modifyLife(-1);
    }
  else if(effect == "duress" && !negated())
    {
		Player* duress_source = target_player.at(0);
		Player* duress_target = target_player.at(1);
		
		if(useCard("attack","attack " + duress_target-> getName() + " or give your weapon to " + current_player -> getName() + '.',duress_source))
		{
			if(!useCard("dodge","dodge or lose one life",duress_target))
				duress_target -> modifyLife(-1);
		}
		else
		{
			GameCard* equip = duress_source -> loseEquipment(2);
			current_player -> recieveCard(equip);
		}
    }
  else
    {
      std::cout << "Card command: \"" + effect + "\" does not exist in the list" << std::endl;
    }
  
  return gameCard;
}

bool Game::negated(const std::string& description)
{
  int nP = self;
  do
  {
	if(useCard("negate", description, players.at(nP)))
		return !negated(description);
	nP = nextPlayer(nP);
  }while(nP != (int)self);
  
  return false;
}
  
void Game::harvest()
{
	//fixa spelare
	target_player.clear();
	target_player.push_back(current_player);
	for(unsigned i = (self +1) % players.size(); i != self; i = (i +1) % players.size())
		target_player.push_back(players.at(i));
	
	//fixa window
	GameCard* card = nullptr;
	Window* harvestWindow = new Window(50,150,600,350);
	for(unsigned i = 0; i < players.size(); ++i)
	{
		card = dynamic_cast<GameCard*>(card_deck -> drawCard());
		harvestWindow -> addCard(card, i* 100, 20);
	}
	harvestWindow -> makeButton("take card",170,250,"pick_card");
	
	//variabler
	card = nullptr;
	unsigned index = 0;
	bool testNegate = true;
	std::string command = "";
	
	//das loop
	while(index != target_player.size())
	{
		//polla negate
		if(testNegate && negated())
		{
			index += 1;
		}
		else
		{
			testNegate = false;
			//polla events
			command = "";
			while(SDL_PollEvent( &event))
			{
				exitCommand(event);
				command = harvestWindow -> handleEvent(event);
			
				if(command == "pick_card")
				{
					for(unsigned i = 0; i < harvestWindow -> getSize(); ++i)
					{
						card = dynamic_cast<GameCard*>(harvestWindow -> getObject(i));
						
						if(card != nullptr && card -> isActive())
						{
							target_player.at(index) -> recieveCard(card);
							//ta bort den från window
							harvestWindow -> remove(i);
							//byt spelare
							target_player.at(index) -> setCurrentPlayer(false);
							index += 1;
							if(index != target_player.size())
								target_player.at(index) -> setCurrentPlayer(true);
							testNegate = true;
						}
					}
				}
			}
			//fixa utskrift
			paint();
			harvestWindow -> paint(screen);
			SDL_Flip(screen.getImage());
			fps.regulateFPS();
		}
	}
	//destroy window
	while(harvestWindow -> getSize() != 1)
	{
		discard_pile -> pushBottom(dynamic_cast<GameCard*>(harvestWindow -> remove(0)));
	}
	delete harvestWindow;
	current_player -> setCurrentPlayer(true);
}

bool Game::acedia()
{
  timer->reset(sett.getTimerTime(), "close");
	bool occured;
	if(!negated("Do you want to negate acedia for player: " + current_player->getName()))
	{
		//fixa fönstret
		GameCard* judge_card = dynamic_cast<GameCard*>(card_deck -> drawCard());
		Window* window_show_card = new Window(200,150,300,400);
		window_show_card -> makeTextbox(5,5,290,70);
		if( judge_card -> getSuit() != hearts)
		{
			occured = true;
			window_show_card -> setText(0,"Acedia triggered - you cannot play your action phase");
		}
		else
		{
			occured = false;
			window_show_card -> setText(0,"Acedia did not trigger - you lucky bastard");			
		}
		
		judge_card -> setPosition(280,225);
		window_show_card -> makeButton("OK",50,320,"close");
		
		
		bool has_window = true;
		while(has_window && running)
		{
		
			while(SDL_PollEvent( &event))
			{
			  exitCommand(event);
			  if(window_show_card->handleEvent(event) == "close")
				has_window = false;
			}
			
			if(timer->time_ran_out() == "close")
				has_window = false;
				
			//måla lite fint
			paint();
			window_show_card->paint(screen);
			judge_card -> paint(screen);
			SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
			fps.regulateFPS();
		}
		
		delete window_show_card;
		if(occured)
		  {
		    timer->reset(sett.getTimerTime(), "time_out");
		  }
		else
		  {
		    timer->reset(sett.getTimerTime(), "end_turn");
		  }
		return occured;
	}
	return false;
}

bool Game::lightningExplode()
{
  std::string tmp_command = timer->getCommand();
  timer->reset(sett.getTimerTime(),"close");
	bool occured;
	if(!negated("Do you want to negate acedia for player: " + current_player->getName()))
	{
		GameCard* judge_card = dynamic_cast<GameCard*>(card_deck -> drawCard());
		Window* window_show_card = new Window(200,150,300,400);
		window_show_card -> makeTextbox(5,5,290,70);
		if( judge_card -> getSuit() == spades && judge_card -> getNumber() >= 2 && judge_card -> getNumber() <=9)
		{
			occured = true;
			window_show_card -> setText(0,"Lightning explode, you lose 3 life");
		}
		else
		{
			occured = false;
			window_show_card -> setText(0,"Lightning safe, card moved to the player to your right");			
		}
		judge_card -> setPosition(280,225);
		window_show_card -> makeButton("OK",50,320,"close");
		bool has_window = true;
		while(has_window && running)
		{
			while(SDL_PollEvent( &event))
			{
			  exitCommand(event);
				if(window_show_card->handleEvent(event) == "close")
				{
					has_window = false;
				}
				
			}
			if(timer->time_ran_out() == "close")
			  {
			    has_window = false;
			  }
			//måla lite fint
			paint();
			
			window_show_card->paint(screen);
			judge_card -> paint(screen);
			SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
			fps.regulateFPS();
		}
		delete window_show_card;
		
		timer->reset(sett.getTimerTime(), tmp_command);
		return occured;
	}
	timer->reset(sett.getTimerTime(), tmp_command);
	return false;
}
