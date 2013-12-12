void Game::run_command(const std::string& what_command)
{
	static unsigned currentTarget = 0;
	static bool duelTargetAttacking = true;
  if(what_command == "")
    {
      return;
    }	
  else if(what_command == "close")
    {
      running = false;
      return;
    }
  else if(what_command == "set_settings")
    {
      m.setVolume(sett.getMusicVolume());
      m.setEffectVolume(sett.getEffectVolume());
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
      m.playSoundEffect(9);
      Window* hero_window = dynamic_cast<Window*>(all_objects.back());
      HeroCard* hero;
      for(unsigned i = 0 ; i < hero_window->getSize() ; ++i)
	{
	  hero = dynamic_cast<HeroCard*>(hero_window->getObject(i));
	  if(hero!=nullptr)
	    {
	      if(hero->isActive())
		{
		  std::cout << "Player: " << self << " took hero: " << hero ->getName() << std::endl;
		  //ge dig själv hero-kortet
		  players.at(self)->setHero(hero);
				
		  //tar bort kortet från window
		  hero_window->remove(i);
					
		  //för varje annat objekt i fönstret
		  while(hero_window->getSize() != 0)
		    {
		      //om det är ett heroCard, flytta in det i hero deck
		      if(dynamic_cast<HeroCard*>(hero_window->getObject(0)) != nullptr)
			{
			  hero_deck->pushBottom(dynamic_cast<HeroCard*>(hero_window->remove(0)));
							
			}
		      //annars ta bort det
		      else
			{
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
		std::cout << "player " << self << " end his/her turn" << std::endl;
      timer->reset(sett.getTimerTime(),"time_out");	 
      state = 5;	//go to discard phase in game
    }

  else if(what_command == "time_out")
    {
		std::cout << "player " << self << " timed out on discard" << std::endl;
      while((unsigned)(players.at(self) -> getLife()) < players.at(self) -> getHandSize())
	{
	  GameCard* card = players.at(self) -> loseCard( players.at(self)->getHandSize()-1);
	  discard_pile -> pushBottom(card);
	}
      state = 6;

      if(timer->checkStarted() == true)
	{
	  timer->stop();
	}
    }
	
  else if(what_command == "play_card")
    {
      std::vector<GameCard*> hand;
      hand = current_player -> getHand();
      for(unsigned i = 0; i < hand.size() ; ++i)
	{
	  if(hand.at(i) -> isActive())
	    {
			hand.at(i) -> setActive(false);
			std::cout << "player " << self << " plays a card" << std::endl;
			timer->reset(sett.getTimerTime(), "end_turn");
	      GameCard* card = current_player -> playCard(i);
	      card = run_effect(card);
	      if(card != nullptr)
		{
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
			std::cout << "player " << self << " discards " << card -> getAbility() << std::endl;
	      discard_pile -> pushBottom(card);
	    }
	}
      timer->reset(sett.getTimerTime(), "time_out");
    }
  else if(what_command == "dodge")
    {	
     std::vector<GameCard*> hand = target_player.at(currentTarget) -> getHand();
      GameCard* card = nullptr;
  	
      for(unsigned i = 0; i < hand.size(); ++i)
	{
	  if(hand.at(i) -> getAbility() == "dodge")
	    {
	      m.playSoundEffect(7);
	      // card = target_player -> playCard(i);
		  card = target_player.at(currentTarget) -> playCard(i);
	      break;
	    }
	}
		
	if(card == nullptr)
	{
		target_player.at(currentTarget) -> modifyLife(-1);
		if(target_player.at(currentTarget) -> getLife() <= 0)
		{
			target_player.at(currentTarget) -> kill();
			cleanPlayer(target_player.at(currentTarget));
		}
	
			std::cout << " the attack is not dodged" << std::endl;
	}
	else
	{
		discard_pile -> pushBottom(card);
			std::cout << " the attack is dodged" << std::endl;
	}	
		target_player.at(currentTarget) -> setCurrentPlayer(false);
		currentTarget += 1;
		
		
		if(target_player.size() == currentTarget)
		{
			currentTarget = 0;
			current_player -> setCurrentPlayer(true);
		//------------------------------
		//----------OBSERVERA-----------
		//------------------------------
			timer->reset(sett.getTimerTime(), "end_turn");
			
			run_command("close_window");
		}	
		else
		{
			target_player.at(currentTarget) -> setCurrentPlayer(true);
		}
    }
  else if(what_command == "take_damage")
    {
	    target_player.at(currentTarget) -> modifyLife(-1);
		if(target_player.at(currentTarget) -> getLife() <= 0)
		{
			target_player.at(currentTarget) -> kill();
			cleanPlayer(target_player.at(currentTarget));
		}
		target_player.at(currentTarget) -> setCurrentPlayer(false);
		
		currentTarget += 1;
		
		if(target_player.size() == currentTarget)
		{
			currentTarget = 0;
			current_player -> setCurrentPlayer(true);
		
			timer->reset(sett.getTimerTime(),"end_turn");
			run_command("close_window");
		}	
		else
		{
			timer->reset(sett.getTimerTime(),"");
			target_player.at(currentTarget) -> setCurrentPlayer(true);
		}
    }
  else if(what_command == "steal_card")
    {
      m.playSoundEffect(4);
      
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
      state = 4;
      timer->reset(sett.getTimerTime(),"end_turn");
    }
  else if(what_command == "steal_time_out")
    {
      m.playSoundEffect(4);
      
      Window* stealWindow = dynamic_cast<Window*>(all_objects.back());
      if(target_player.at(0)->getHand().size() > 0)
	{
	  current_player->recieveCard(target_player.at(0)->loseCard(0));
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
      state = 4;
      timer->reset(sett.getTimerTime(),"end_turn");
      
    }
  else if(what_command == "dismantle_card")
    {
      m.playSoundEffect(3);
      
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
	{
	  delete dismantleWindow -> getObject(0);
	  dismantleWindow -> remove(0);
	}
      //delete button
      delete dismantleWindow -> remove(dismantleWindow -> getSize()-1);
      
      while(dismantleWindow -> getSize() != 0)
	dismantleWindow -> remove(0);
      
      target_player.clear();
      run_command("close_window");
      state = 4;
    }
  else if(what_command == "dismantle_time_out")
    {
      std::cerr << "auto dismantla kort" << std::endl;
      Window* dismantleWindow = dynamic_cast<Window*>(all_objects.back());
  std::cerr << "windpw skapat" << std::endl;
      m.playSoundEffect(3);
      std::cerr << "ljud spelat" << std::endl;
      if(target_player.at(0)->getHand().size() > 0)
	{
	  discard_pile -> pushBottom(target_player.at(0) -> loseCard(0));//what if no cards
	}
      std::cerr << "kort auto dismantlat" << std::endl;
      
      //delete dummys
      while(dynamic_cast<HeroCard*>(dismantleWindow -> getObject(0)) != nullptr)
	{
	  delete dismantleWindow -> getObject(0);
	  dismantleWindow -> remove(0);
	}
      //delete button
      delete dismantleWindow -> remove(dismantleWindow -> getSize()-1);
      
      while(dismantleWindow -> getSize() != 0)
	dismantleWindow -> remove(0);
      
      timer->reset(sett.getTimerTime(), "end_turn");
      target_player.clear();
      run_command("close_window");
      state = 4;
      std::cerr << "state = 4" << std::endl;
      
    }
  else if(what_command == "barbarian_attack")
    {
		// static int barbarianTarget = 0;
		bool playedAttack = false;
      timer->reset(sett.getTimerTime(),"barbarian_attack");
		
      std::vector<GameCard*> hand = target_player.at(currentTarget) -> getHand();
      for(unsigned i = 0; i < hand.size(); ++i)
	{
	  if(hand.at(i) -> getAbility() == "attack")
	    {
	      playedAttack = true;
	      discard_pile -> pushBottom(target_player.at(currentTarget) -> loseCard(i));
	      break;
	    }
	}
      
      if(!playedAttack)
	  {
	    target_player.at(currentTarget) -> modifyLife(-1);
		if(target_player.at(currentTarget) -> getLife() <= 0)
		{
			target_player.at(currentTarget) -> kill();
			cleanPlayer(target_player.at(currentTarget));
		}
	  }
		  
      //nästa spelare (devil)(huehuehue)
      	target_player.at(currentTarget) -> setCurrentPlayer(false);
		currentTarget += 1;
      
      if(currentTarget == target_player.size())
	{
	  currentTarget = 0;
	  //döda fönstrett!!
	  run_command("close_window");
	  
	  current_player -> setCurrentPlayer(true);
	  target_player.clear();
	  timer->reset(sett.getTimerTime(),"end_turn");
	}
	else
		target_player.at(currentTarget) -> setCurrentPlayer(true);

    }
  else if(what_command == "arrow_attack")	
    {
	  // static int arrowTarget = 0;
      timer->reset(sett.getTimerTime(),"arrow_attack");
	  
      bool playedDodge = false;
      std::vector<GameCard*> hand = target_player.at(currentTarget) -> getHand();
      for(unsigned i = 0; i < hand.size(); ++i)
	{
	  if(hand.at(i) -> getAbility() == "dodge")
	    {
	      playedDodge = true;
	      discard_pile -> pushBottom(target_player.at(currentTarget) -> loseCard(i));
	      break;
	    }
	}
      
      if(!playedDodge)
	  {
	    target_player.at(currentTarget) -> modifyLife(-1);
		if(target_player.at(currentTarget) -> getLife() <= 0)
		{
			target_player.at(currentTarget) -> kill();
			cleanPlayer(target_player.at(currentTarget));
		}
	  }
      
	//nästa spelare (devil)(huehuehue)
	target_player.at(currentTarget) -> setCurrentPlayer(false);
	currentTarget += 1;
      
      if(currentTarget == target_player.size())
	{
	  currentTarget = 0;
	  //döda fönstrett!!
	  
	  run_command("close_window");
	  current_player -> setCurrentPlayer(true);
	  target_player.clear();
	  timer->reset(sett.getTimerTime(),"end_turn");
	}
	else
		target_player.at(currentTarget) -> setCurrentPlayer(true);
    }
  else if(what_command == "pick_card")
    {
      // static int harvestTarget = 0;
     
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
	      index = i;
	      break;				//card is found and stored
	    }
	}
      
      //picka kort
      if(index != -1)
	{
	  card -> setActive(false);
	  target_player.at(currentTarget) -> recieveCard(card);
	  harvestWindow -> remove(index);
	}
    else if(harvestWindow -> getSize() != 1)
		return;	//inget kort valt!
      
	//byt spelare
	target_player.at(currentTarget) -> setCurrentPlayer(false);
	currentTarget += 1;
	timer->reset(sett.getTimerTime(),"");
      
      //om sig själv destruera fönstrett
      if(currentTarget == target_player.size())
	{
	  currentTarget = 0;
	  //fixa bort kort som negatats
	  while(harvestWindow -> getSize() != 1)
		discard_pile -> pushBottom(dynamic_cast<GameCard*>(harvestWindow -> remove(0)));
		
	  run_command("close_window");
		
	  current_player -> setCurrentPlayer(true);
	  target_player.clear();
	}
	else
		target_player.at(currentTarget) -> setCurrentPlayer(true);
    }
  else if(what_command == "duel_damage")
	{
		timer->reset(sett.getTimerTime(), "end_turn");
			
		if(duelTargetAttacking)
		{
			target_player.at(0) -> modifyLife(-1);
			if(target_player.at(0) -> getLife() <= 0)
			{
				target_player.at(0) -> kill();
				cleanPlayer(target_player.at(0));
			}
		}
		else 
		{
			current_player -> modifyLife(-1);
			if(current_player -> getLife() <= 0)
			{
				current_player -> kill();
				cleanPlayer(current_player);
			}
		}

		target_player.at(0) -> setCurrentPlayer(false);
		current_player -> setCurrentPlayer(true);
		
		run_command("close_window");
	}
  else if(what_command == "duel_attack")
    {
      timer->reset(sett.getTimerTime(), "end_turn");
      // static bool duelTargetAttacking = true;
      int hasAttack = -1;
      std::vector<GameCard*> hand;
	  
      //kollar om han har en attack
      if(duelTargetAttacking)
		hand = target_player.at(0) -> getHand();
      else
		hand = current_player -> getHand();
      
      for(unsigned i = 0; i < hand.size(); ++i)
		 if(hand.at(i) -> getAbility() == "attack")
			hasAttack = i;
      
    if(hasAttack != -1)
		if(duelTargetAttacking)
			discard_pile -> pushBottom(target_player.at(0) -> playCard(hasAttack));
		else
			discard_pile -> pushBottom(current_player -> playCard(hasAttack));
    else
	{
	  current_player -> setCurrentPlayer(true);
	  target_player.at(0) -> setCurrentPlayer(false);
	  if(duelTargetAttacking)
	  {
	    target_player.at(0) -> modifyLife(-1);
		if(target_player.at(0) -> getLife() <= 0)
		{
			target_player.at(0) -> kill();
			cleanPlayer(target_player.at(0));
		}
	  }
	  else
	  {
	    current_player -> modifyLife(-1);
		if(current_player -> getLife() <= 0)
		{
			current_player -> kill();
			cleanPlayer(current_player);
		}
	  }
	  
	  duelTargetAttacking = true;
	  //clean up
	  run_command("close_window");
	  return;
	}
      duelTargetAttacking = !duelTargetAttacking;
      
      target_player.at(0) -> setCurrentPlayer(duelTargetAttacking);
      current_player -> setCurrentPlayer(!duelTargetAttacking);
    }
  else if(what_command == "give_weapon")
    {
      //döda inte :( 
      if(current_player -> equipment.weapon != nullptr)
	discard_pile -> pushBottom(current_player -> loseEquipment(2));
      std::swap(current_player -> equipment.weapon,source_player -> equipment.weapon);
      
      run_command("close_window");
      //target_player.clear();
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
	  GameCard* card = source_player -> playCard(index);
	  
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
		if(what_command != "activated")
			std::cout << "Command: \"" + what_command + "\" is not found in command list" << std::endl;
    }
  return;
}

