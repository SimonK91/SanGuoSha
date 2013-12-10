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
      if(target_player != nullptr)
	{
	  for(unsigned i = 0; i < players.size(); ++i)
	    {
	      if(players.at(i) == target_player)
		{
		  self = i;
		}
	    }
	  timer->reset(sett.getTimerTime(),"take_damage");
	  
	  Window* dodgeWindow = new Window(160,250,500,250);
	  dodgeWindow -> makeButton("Dodge",37,70,"dodge");
	  dodgeWindow -> makeButton("Take damage",260,70, "take_damage");
	  add_window(dodgeWindow);
	  has_window = true;
	  
	  target_player -> setCurrentPlayer(true);
	  current_player -> setCurrentPlayer(false);
	}
      else
	{
	  std::cout << "no player active... :(" << std::endl;
	}
    }
  else if(effect == "heal")
    {
      std::cout << "heal effect:" << std::endl;
      std::cout << "target_player == nullptr: " << std::boolalpha << (target_player == nullptr) <<std::endl;
      std::cout << "current_player == nullptr: " << std::boolalpha << (current_player == nullptr) <<std::endl;
      if(target_player != nullptr  && target_player -> getLife() <= 0)
	{
	  target_player -> modifyLife(1);
	}
      else
	{
	  current_player -> modifyLife(1);
	}
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
      if(target_player != nullptr)
	{
	  target_player -> addJudgementCard(gameCard);
	  gameCard = nullptr;
	}
      else
	{
	  std::cout << "ingen vald spelare att spela acedia på :( "<< std::endl;
	}
    }
  else if(effect == "lightning")
    {
      if(target_player != nullptr)
	{
	  target_player -> addJudgementCard(gameCard);
	  gameCard = nullptr;
	}
      else
	std::cout << "ingen vald spelare att spela lightning på :( "<< std::endl;
    }
  else if(effect == "steal" && !negated())
    {
     
      if(target_player != nullptr)
	{
	  timer->reset(sett.getTimerTime(),"steal_time_out");
	  state = 7;
	  Window* stealWindow = new Window(200,150,600,350);
	  HeroCard* dummy = new HeroCard("back.png", "42 gray 0 dummy");	  
	  std::vector<GameCard*> targetHand = target_player -> getHand();
	  
	  for(unsigned i = 0; i < targetHand.size(); ++i)
	    {
	      stealWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
	    }
	  //add equipment
	  if(target_player -> equipment.weapon != nullptr)
	    {
	      stealWindow -> addCard(target_player -> equipment.weapon,0, 240);
	    }
	  if(target_player -> equipment.shield != nullptr)
	    {
	      stealWindow -> addCard(target_player -> equipment.shield, 100, 240);
	    }
	  if(target_player -> equipment.off_horse != nullptr)
	    {
	      stealWindow -> addCard(target_player -> equipment.off_horse, 200, 240);
	    }
	  if(target_player -> equipment.def_horse != nullptr)
	    {
	      stealWindow -> addCard(target_player -> equipment.def_horse, 300, 240);
	    }
	  	  
	  stealWindow -> makeButton("Steal",170,250, "steal_card");
	  add_window(stealWindow);
	  has_window = true;
	  std::cerr << "FORBI steal skapandet" << std::endl;
	}
      else
	std::cout << "No steal... :(" << std::endl;
    }
  else if(effect == "dismantle" && !negated())
    {
      
      if(target_player != nullptr)
	{
	  state = 7;
	  timer->reset(sett.getTimerTime(), "dismantle_time_out");
	  Window* dismantleWindow = new Window(200,150,600,350);
	  HeroCard* dummy = new HeroCard("back.png", "42 gray 0 dummy");
	  //getEquipment() måste implementeras!
	  std::vector<GameCard*> targetHand = target_player -> getHand();
			
	  for(unsigned i = 0; i < targetHand.size(); ++i)
	    {
	      dismantleWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
	    }
	  //add equipment
	  if(target_player -> equipment.weapon != nullptr)
	    dismantleWindow -> addCard(target_player -> equipment.weapon,0, 240);
	  if(target_player -> equipment.shield != nullptr)
	    dismantleWindow -> addCard(target_player -> equipment.shield, 100, 240);
	  if(target_player -> equipment.off_horse != nullptr)
	    dismantleWindow -> addCard(target_player -> equipment.off_horse, 200, 240);
	  if(target_player -> equipment.def_horse != nullptr)
	    dismantleWindow -> addCard(target_player -> equipment.def_horse, 300, 240);
			
			
	  dismantleWindow -> makeButton("dismantle",170,250, "dismantle_card");
	  add_window(dismantleWindow);
	  has_window = true;
	}
      else
	std::cout << "No dismantle... :(" << std::endl;
    }
  else if(effect == "barbarian")
    {
      m.playSoundEffect(5);
      timer->reset(sett.getTimerTime(),"barbarian_attack");
      Window* barbarianWindow = new Window(50,350,350,200);
      barbarianWindow -> makeTextbox(20,40,310,30);
      barbarianWindow -> makeButton("Attack!!!",70,100,"barbarian_attack");		
      barbarianWindow -> setText(0,"   Attack the barbarians or lose a life!");
      add_window(barbarianWindow);
      has_window = true;
		
      //current player is going to go around
      current_player -> setCurrentPlayer(false);
      target_player = players.at((self +1) % players.size());
      target_player -> setCurrentPlayer(true);
    }
  else if(effect == "raining_arrows")
    {
      m.playSoundEffect(6);
      timer->reset(sett.getTimerTime(),"arrow_attack");
      Window* arrowWindow = new Window(50,350,350,200);		
      arrowWindow -> makeTextbox(40,40,270,30);
      arrowWindow -> makeButton("Dodge!!!",70,100,"arrow_attack");		
      arrowWindow -> setText(0," Dodge the arrows or lose a life!");
      add_window(arrowWindow);
      has_window = true;
		
      //current player is going to go around
      current_player -> setCurrentPlayer(false);
      target_player = players.at((self +1) % players.size());
      target_player -> setCurrentPlayer(true);
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
      target_player = current_player;
    }
  else if(effect == "duel" && !negated())
    {
      if(target_player != nullptr)
	{
	  Window* duelWindow = new Window(50,350,350,200);
	  duelWindow -> makeTextbox(40,40,270,30);
	  duelWindow -> setText(0,"You are dueld. Attack or lose a life!");
	  duelWindow -> makeButton("Duel!", 70, 100, "duel_attack");
	  add_window(duelWindow);
	  current_player -> setCurrentPlayer(false);
	  target_player -> setCurrentPlayer(true);
	  has_window = true;
	}
      else
	{
	  std::cout << "sadface :( no duelist..." <<std::endl;
	}
    }
  else if(effect == "duress" && !negated())
    {
      if(target_player != nullptr)
	{
	  make_button("Attack him!",100,100,"duress_attack");
	  source_player = target_player;
	  target_player = nullptr;
	}
      else
	std::cout << "no target for duress :( " << std::endl;
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
		//add_window(negate_window);
		has_window = true;
		cur_player -> setCurrentPlayer(true);
		hand = cur_player ->getHand();
		card = nullptr;
		while(has_window)
		{
			while(SDL_PollEvent( &event))
			{
				command = negate_window->handleEvent(event);
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
					
			}
			//måla lite fint
			paint();
			
			negate_window->paint(screen);
			SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
			fps.regulateFPS();
		}
		do
		{
			if(++i == players.size())
				i = 0;
		}while(players.at(i) ->getLife() <=0);
		cur_player -> setCurrentPlayer(false);
		cur_player = players.at(i);
	}
	while(cur_player != current_player && !isNegated);
	current_player -> setCurrentPlayer(true);
	delete negate_window;
	selected_card = played_card;
	if(isNegated)
		return !negated();
	
	return false;
}