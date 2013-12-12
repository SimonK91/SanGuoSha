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

	  // timer->reset(sett.getTimerTime(),"take_damage");
	  
		// Window* dodgeWindow = new Window(160,250,500,250);
		// dodgeWindow -> makeButton("Dodge",37,70,"dodge");
		// dodgeWindow -> makeButton("Take damage",260,70, "take_damage");
		// add_window(dodgeWindow);
		// has_window = true;

		if(!useCard("dodge", "dodge the attack or lose a life",target_player.at(0)))
			target_player.at(0) ->modifyLife(-1);
		// target_player.at(0) -> setCurrentPlayer(true);
		// current_player -> setCurrentPlayer(false);
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
	  for(int nP = nextPlayer(); nP != self ; nP = nextPlayer(nP))
			if(!useCard("attack","attack or lose a life",players.at(nP)))
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
      timer->reset(sett.getTimerTime(),"arrow_attack");
	  
		Window* arrowWindow = new Window(50,350,350,200);
		
		// barbarianWindow -> addCard(gameCard,400,350);
		arrowWindow -> makeTextbox(40,40,270,30);
		arrowWindow -> makeButton("Dodge!!!",70,100,"arrow_attack");
		
		arrowWindow -> setText(0," Dodge the arrows or lose a life!");

		add_window(arrowWindow);
		has_window = true;
		
		//current player is going to go around
		current_player -> setCurrentPlayer(false);
		for(int i = (self +1) % players.size(); i != self; i = (i +1) % players.size())
			target_player.push_back(players.at(i));
			
		target_player.at(0) -> setCurrentPlayer(true);
    }
  else if(effect == "harvest")
    {
		Window* harvestWindow = new Window(50,150,600,350);
		for(unsigned i = 0; i < players.size(); ++i)
		{
			card = dynamic_cast<GameCard*>(card_deck -> drawCard());
			harvestWindow -> addCard(card, i* 100, 20);
		}
		harvestWindow -> makeButton("take card",170,250,"pick_card");
		add_window(harvestWindow);
		has_window = true;
		
		//fix target_players
		target_player.clear();
		target_player.push_back(current_player);
		for(int i = (self +1) % players.size(); i != self; i = (i + 1) % players.size())
			target_player.push_back(players.at(i));
		
    }
  else if(effect == "duel" && !negated())
    {
		Window* duelWindow = new Window(50,350,350,200);
		duelWindow -> makeTextbox(40,40,270,30);
		duelWindow -> setText(0,"You are dueld. Attack or lose a life!");
		duelWindow -> makeButton("Duel!", 70, 100, "duel_attack");
		add_window(duelWindow);
		current_player -> setCurrentPlayer(false);
		target_player.at(0) -> setCurrentPlayer(true);
		has_window = true;
    }
  else if(effect == "duress" && !negated())
    {
		current_player -> setCurrentPlayer(false);
		target_player.at(0) -> setCurrentPlayer(true);
		
		//skapa ett fönster med val
		Window* duressWindow = new Window(160,250,500,250);
		duressWindow -> makeTextbox(40,40,420,30);
		duressWindow -> setText(0,"Attack " + target_player.at(1) -> getHeroName()  + " or lose your weapon to " + current_player -> getHeroName());
		
		duressWindow -> makeButton("Attack",37,170,"duress_attack_respons");
		duressWindow -> makeButton("Give weapon",260,170,"give_weapon");
		has_window = true;
		add_window(duressWindow);
    }
  else
    {
      std::cout << "Card command: \"" + effect + "\" does not exist in the list" << std::endl;
    }
  
  return gameCard;
}

bool Game::negated()
{
  GameCard* played_card = selected_card;
  int i = self;
  Player* cur_player = players.at(self);
  Window* negate_window = new Window(250,350,400,200);
  negate_window->makeButton("Negate",30,120,"negate_true");
  negate_window->makeButton("Skip",280,120,"negate_false");
  std::string command;
  bool isNegated = false;
  current_player->setCurrentPlayer(false);
  GameCard* card;
  std::vector<GameCard*> hand;
  do
    {
      timer->reset(sett.getTimerTime(), "negate_false");
      has_window = true;
      cur_player -> setCurrentPlayer(true);
      hand = cur_player ->getHand();
      card = nullptr;
      while(has_window && running)
	{
	  std::string timer_cmp = timer->time_ran_out();
	  while(SDL_PollEvent( &event))
	    {
	      exitCommand(event);
	       command = negate_window->handleEvent(event);
	    }
	  if(command != "negate_true" && command != "negate_false" && timer_cmp != "")
	    {
	      command = timer_cmp;
	    }
	  if(command == "negate_true")
	    {
	      for(unsigned i = 0; i < hand.size(); ++i)
		{
		  if(hand.at(i) -> getAbility() == "negate")
		    {
		      card = cur_player -> playCard(i);
		      isNegated = true;
		      break;
		    }
		}
	      
	      if(card != nullptr)
		discard_pile -> pushBottom(card);
	      
	      has_window = false;
	      
	    }
	  else if(command == "negate_false")
	    {
	      has_window = false;
	    }

	  paint();
	  negate_window->paint(screen);
	  SDL_Flip(screen.getImage());
	  fps.regulateFPS();
	}
      do
	{
	  if(++i == players.size())
	    i = 0;
	}while(players.at(i) ->getLife() <=0);

      if(cur_player != players.at(i))
	{
	  timer->reset(sett.getTimerTime(), "negate_false");
	  command = "";
	}
      cur_player -> setCurrentPlayer(false);
      cur_player = players.at(i);

    }while(cur_player != current_player && !isNegated);
  
  current_player -> setCurrentPlayer(true);
  delete negate_window;
  selected_card = played_card;
  
  if(isNegated)
    return !negated();
  timer->reset(sett.getTimerTime(), "end_turn");
  return false;
}

bool Game::acedia()
{
  timer->reset(sett.getTimerTime(), "close");
	bool occured;
	if(!negated())
	{
	
	
		std::string command;
		
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
		
		has_window = true;
		while(has_window && running)
		{
			command = timer->time_ran_out();
			while(SDL_PollEvent( &event))
			{
			  exitCommand(event);
			  if(command != "")
				command = window_show_card->handleEvent(event);
			}
			if(command == "close")
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
	if(!negated())
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
		has_window = true;
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
