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
		has_attacked = true;
		if(!shieldBlock("attack"))
		{
			if(!useCard("dodge", "dodge the attack or lose a life",target_player.at(0)))
			{
				if(current_player -> equipment.weapon != nullptr && current_player -> equipment.weapon ->getAbility() == "weapon4") //unicorn bow
				{
					UnicornBow();
					modifyLife(target_player.at(0),-1);
				}
				else if(current_player -> equipment.weapon != nullptr && current_player -> equipment.weapon -> getAbility() == "weapon8") //frost blade
				{
					if(frostBladeLoseLife())
						modifyLife(target_player.at(0), -1);
					else
					{
						//fixa med dismantle
						GameCard* card;
						card = takeAwayCard(target_player.at(0),false);
						discard_pile -> pushBottom(gameCard);
						card = takeAwayCard(target_player.at(0),false);
						discard_pile -> pushBottom(gameCard);
					}
				}
				else
				{
					modifyLife(target_player.at(0),-1);
				}
			}
		}
		else
		{
			{
				if(current_player -> equipment.weapon != nullptr && current_player -> equipment.weapon ->getAbility() == "weapon2") //green dragon cresent
				{
					bool done = false;
					do
					{
						if(useCard("attack", "your attack was dodged, continue attack the target?", current_player))
						{
							if(!useCard("dodge", "dodge the attack or lose a life",target_player.at(0)))
							{
								modifyLife(target_player.at(0),-1);
								done = true;
							}
						}
						else
							done = true;
					}while(!done);
				}				
			}
		}
    }
	
  else if(effect == "heal")
    {
		if(target_player.size() != 0 && target_player.at(0) -> getLife() <= 0)
		{
			modifyLife(target_player.at(0),-1);
		}
		else
			modifyLife(current_player,1);
    }
  else if(effect == "off_horse")
    {
      m.playSoundEffect(2);
      gameCard = current_player -> equipStuff(gameCard,3);
	  if(gameCard != nullptr)
		discard_pile -> pushBottom(gameCard);
    }
  else if(effect == "def_horse")
    {
      m.playSoundEffect(2);
      gameCard = current_player -> equipStuff(gameCard,4);
	  if(gameCard != nullptr)
		discard_pile -> pushBottom(gameCard);
    }
  else if(effect.substr(0,6) == "weapon")
    {
      m.playSoundEffect(1);
      gameCard = current_player -> equipStuff(gameCard,1);
	  if(gameCard != nullptr)
		discard_pile -> pushBottom(gameCard);
    }
  else if(effect.substr(0,6) == "shield")
    {
      m.playSoundEffect(0);
      gameCard = current_player -> equipStuff(gameCard,2);
	  if(gameCard != nullptr)
		discard_pile -> pushBottom(gameCard);
    }
  else if(effect == "peach_garden")
    {
		for(Player* p : players)
		{
			if(p->getLife() != p->getMaxLife() && !negated())
			{
				modifyLife(p,1);
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
  else if(effect == "steal" && !negated("negate steal on " + target_player.at(0)->getName()))
    {
     
	  timer->reset(sett.getTimerTime(),"steal_time_out");
	  state = 7;
	 
	 	Window* stealWindow = new Window(195,30,600,500);

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
			
			
		stealWindow -> makeButton("Steal",170,450, "steal_card");
		add_window(stealWindow);
		has_window = true;
    }
  else if(effect == "dismantle" && !negated("Negate dismantle on " + target_player.at(0)->getName()))
    {
	  state = 7;
	  timer->reset(sett.getTimerTime(), "dismantle_time_out");
	  
		Window* dismantleWindow = new Window(195,30,600,500);
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
			
		dismantleWindow -> makeButton("dismantle",170,450, "dismantle_card");
		add_window(dismantleWindow);
		has_window = true;
	}
  else if(effect == "barbarian")
    {
      m.playSoundEffect(5);
	  for(int nP = nextPlayer(); nP != (int)self ; nP = nextPlayer(nP))
	  {
			if(!negated(" negate barbarian for " + players.at(nP)->getName()) && !useCard("attack","attack the barbarians or lose a life",players.at(nP)))
			{
				modifyLife(players.at(nP),-1);
			}
		}
    }
  else if(effect == "raining_arrows")
    {
      m.playSoundEffect(6);
	  for(int nP = nextPlayer(); nP != (int)self ; nP = nextPlayer(nP))
	  {
			if(!negated("negate raining arrow for " + players.at(nP) ->getName()) && !useCard("dodge","dodge the rain of arrows or lose a life",players.at(nP)))
			{
				modifyLife(players.at(nP),-1);
			}
		}	
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
			modifyLife(defender,-1);
		else
			modifyLife(offender,-1);
    }
  else if(effect == "duress" && !negated())
    {
		Player* duress_source = target_player.at(0);
		Player* duress_target = target_player.at(1);
		
		if(useCard("attack","attack " + duress_target-> getName() + " or give your weapon to " + current_player -> getName() + '.',duress_source))
		{
			if(!useCard("dodge","dodge or lose one life",duress_target))
				modifyLife(duress_target,-1);
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
  unsigned nP = self;
  do
  {
	if(useCard("negate", description, players.at(nP)))
		return !negated(description);
	nP = nextPlayer(nP);
  }while(nP != self);
  
  return false;
}
  
void Game::harvest()
{
	std::string old_timer_command = timer -> getCommand();

	GameCard* card = nullptr;
	//fixa window
	Window* harvestWindow = new Window(50,50,600,350);
	
	//kolla antalet spelare som är vid liv
	int num_cards = 0;
	for(int i = 0 ; i < players.size() ; ++i)
	{
		if(players.at(i) ->isAlive())
			++num_cards;
	}
	
	//dra ett kort för varje sådan spelare
	for(unsigned i = 0; i < num_cards; ++i)
	{
		card = dynamic_cast<GameCard*>(card_deck -> drawCard());
		harvestWindow -> addCard(card,20 + i*(400/(num_cards-1)), 20);
	}
	harvestWindow -> makeButton("take card",50,250,"pick_card");
	harvestWindow -> makeButton("show hand",270,250,"show_hand");
	
	//variabler
	card = nullptr;
	std::string command = "";
	//bool has_window = true;
	unsigned nP = self;
	//das loop
	do
	{
		if(!negated())
		{
			bool taken = false;
			bool show_hand = false;
			while(!taken)
			{
				command = "";
				while(SDL_PollEvent(&event))
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
								card -> setActive(0);
								players.at(nP) -> recieveCard(card);
								//ta bort den från window
								harvestWindow -> remove(i);
								nP = nextPlayer(nP);
								taken = true;
							}
						}
					}
					else if(command == "show_hand")
					{
						show_hand = true;
					}
				}
				//fixa utskrift
				if(!taken)
				{
					applySurface(0,0,background,screen);
					for(unsigned i = 0; i < all_objects.size() ; ++i)
					{
						all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
					}
				
					if(timer->checkStarted() == true)
					{
						timer->paint(screen);
					}
				
					if(show_hand)
					{
						players.at(nP)->paint(screen);
					}
					else
					{	
						players.at(nP)->setPos(680,240);
						players.at(nP)->paint(screen,680,240);
					}
					harvestWindow -> paint(screen);
					SDL_Flip(screen.getImage());
					fps.regulateFPS();
				}
			}
		}
		else
			nP = nextPlayer(nP);
	}while(nP != self);
	
	//destroy window
	while(harvestWindow -> getSize() != 1)
	{
		discard_pile -> pushBottom(dynamic_cast<GameCard*>(harvestWindow -> remove(0)));
	}
	delete harvestWindow;
	//current_player -> setCurrentPlayer(true);
	
	timer->reset(sett.getTimerTime(), old_timer_command);
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
	if(!negated("Do you want to negate Lightning for player: " + current_player->getName()))
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

void Game::UnicornBow()
{
	std::string old_timer_command = timer -> getCommand();
	timer->reset(sett.getTimerTime(), "skip");
	std::string command;
	Window options(175,125,400,400);
	options.makeTextbox(30,30,340,80,25);
	options.setText(0,"your attack hit the target, with your Bow you are able to kill one of his/her horses");
	if(target_player.at(0) -> equipment.off_horse != nullptr)
	{
		options.makeButton("offensive",15,330,"off_horse");
	}
	if(target_player.at(0) -> equipment.def_horse != nullptr)
	{
		options.makeButton("defensive",215,330,"def_horse");
	}
	options.makeButton("Skip",115,230,"skip");
	bool has_window = true;
	GameCard* card;
	while(has_window)
	{
		command = timer->time_ran_out();
		while(SDL_PollEvent( &event))
		{
			exitCommand(event);
			if(command == "")
				command = options.handleEvent(event);
		}
	
		if(command == "skip")
		{
			has_window = false;
		}
		else if(command == "def_horse")
		{
			card = target_player.at(0) -> loseEquipment(0);
			discard_pile -> pushBottom(card);
			has_window = false;
		}
		else if(command == "off_horse")
		{
			card = target_player.at(0) -> loseEquipment(1);
			discard_pile -> pushBottom(card);
			has_window = false;
		}
		//LiTHe paint
		if(has_window)
		{
			applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
			for(unsigned i = 0; i < all_objects.size() ; ++i)
			{
				all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
			}
		
			if(timer->checkStarted() == true)
			{
				timer->paint(screen);
			}
		
			options.paint(screen);
			target_player.at(0)->setPos(600,240);
			target_player.at(0)->paint(screen,600,240);
		
			SDL_Flip(screen.getImage());
			fps.regulateFPS();
		}
	}
	
	timer->reset(sett.getTimerTime(), old_timer_command);
}

bool Game::frostBladeLoseLife()
{
	std::string old_timer_command = timer -> getCommand();
	timer->reset(sett.getTimerTime(), "damage");
	std::string command;
	Window options(175,125,400,400);
	options.makeTextbox(30,30,340,80,25);
	options.setText(0,"Target lose a life point or you discard 2 cards from the target");
	bool occured = false;
	options.makeButton("Do Damage",15,330,"damage");
	options.makeButton("Dismantle",215,330,"dismantle");

	bool has_window = true;
	while(has_window)
	{
		command = timer->time_ran_out();
		while(SDL_PollEvent( &event))
		{
			exitCommand(event);
			if(command == "")
				command = options.handleEvent(event);
		}
	
		if(command == "damage")
		{
			occured = true;
			has_window = false;
		}
		else if(command == "dismantle")
		{
			occured = false;
			has_window = false;
		}
		//LiTHe paint
		if(has_window)
		{
			applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
			for(unsigned i = 0; i < all_objects.size() ; ++i)
			{
				all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
			}
		
			if(timer->checkStarted() == true)
			{
				timer->paint(screen);
			}
		
			options.paint(screen);
			current_player -> setPos(600,240);
			current_player -> paint(screen,600,240);
		
			SDL_Flip(screen.getImage());
			fps.regulateFPS();
		}
	}
	
	timer->reset(sett.getTimerTime(), old_timer_command);
	return occured;
}

GameCard* Game::takeAwayCard(Player* target, bool includeJudgement)
{
	Window* takeAwayCardWindow = new Window(150,50,600,600);
	std::vector<GameCard*> targetHand = target_player.at(0) -> getHand();
		
	for(unsigned i = 0; i < targetHand.size(); ++i)
	{
		takeAwayCardWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
	}
	//add equipment
	if(target_player.at(0) -> equipment.weapon != nullptr)
		takeAwayCardWindow -> addCard(target_player.at(0) -> equipment.weapon,0, 240);
	if(target_player.at(0) -> equipment.shield != nullptr)
		takeAwayCardWindow -> addCard(target_player.at(0) -> equipment.shield, 100, 240);
	if(target_player.at(0) -> equipment.off_horse != nullptr)
		takeAwayCardWindow -> addCard(target_player.at(0) -> equipment.off_horse, 200, 240);
	if(target_player.at(0) -> equipment.def_horse != nullptr)
		takeAwayCardWindow -> addCard(target_player.at(0) -> equipment.def_horse, 300, 240);
			
	if(includeJudgement)
	{
		//få tag i alla judgement cards!!! måste fixas senare :) 
		// takeAwayCardWindow -> addCard();
	}
	
	takeAwayCardWindow -> makeButton("Take Card",170,500, "take_card");
	
	GameCard* card = nullptr;
	std::string old_timer_command = timer -> getCommand();
	timer->reset(sett.getTimerTime(), "take_last");
	std::string command;
	bool has_window = true;
	
	while(has_window)
	{
		command = timer->time_ran_out();
		while(SDL_PollEvent( &event))
		{
			exitCommand(event);
			if(command == "")
				command = takeAwayCardWindow -> handleEvent(event);
		}
		
		if(command == "take_card")
		{
			//kolla alla korten
			Card* c = nullptr;
			for(unsigned i = 0 ; i < takeAwayCardWindow->getSize() ; ++i)
			{
				c = dynamic_cast<Card*>(takeAwayCardWindow -> getObject(i));
				if(c != nullptr && c -> isActive())
				{
					if(i < target -> getHandSize())
						card = target -> loseCard(i);
					else
					{
						GameCard* gc = dynamic_cast<GameCard*>(c);
						if((gc -> getAbility()).substr(0,6) == "weapon")
							card = target -> loseEquipment(2);
						else if((gc -> getAbility()).substr(0,6) == "shield")
							card = target -> loseEquipment(3);
						else if(gc -> getAbility() == "off_horse")
							card = target -> loseEquipment(1);	
						else if(gc -> getAbility() == "def_horse")
							card = target -> loseEquipment(0);
					}
					has_window = false;
				}
			}
		}
		else if(command == "take_last")
		{
			card = target -> loseCard((target -> getHandSize()) - 1);
			has_window = false;
		}
		//LiTHe paint
		if(has_window)
		{
			applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
			for(unsigned i = 0; i < all_objects.size() ; ++i)
			{
				all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
			}
		
			if(timer->checkStarted() == true)
			{
				timer->paint(screen);
			}
		
			takeAwayCardWindow -> paint(screen);
			current_player -> setPos(750,240);
			current_player -> paint(screen,750,240);
		
			SDL_Flip(screen.getImage());
			fps.regulateFPS();
		}
	}
	
	timer->reset(sett.getTimerTime(), old_timer_command);
	return card;
}