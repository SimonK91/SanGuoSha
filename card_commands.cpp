GameCard* Game::run_effect(Object::GameCard* gameCard)
{
  GameCard* card = nullptr;
  std::string effect = gameCard -> getAbility();
  
  if(effect == "draw2")
    {
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
	  for(int i = 0; i < players.size(); ++i)
	    {
	      if(players.at(i) == target_player)
		{
		  self = i;
		}
	    }
	  if(timer->checkStarted() == true)
	    {
	      timer->stop();
	    }
	  timer->start(5);
	  timer->setCommand("take_damage");
	  std::cout << "ny timer med take_damage" << std::endl;
	  Window* dodgeWindow = new Window(230,250,250,200);
	  
	  has_window = true;
	  dodgeWindow -> makeButton("Dodge",30,25,"dodge");
	  dodgeWindow -> makeButton("Take damage",30,100, "take_damage");
	  add_window(dodgeWindow);
	  target_player -> setCurrentPlayer(true);
	  current_player -> setCurrentPlayer(false);
	}
      else
	std::cout << "no player active... :(" << std::endl;
    }
  else if(effect == "heal")
    {
      if(target_player != nullptr  && target_player -> getLife() <= 0)
	{
	  target_player -> modifyLife(1);
	}
      else
	current_player -> modifyLife(1);
    }
  else if(effect == "off_horse")
    {
      if(current_player -> equipment.off_horse != nullptr)
	{
	  std::swap(current_player -> equipment.off_horse, gameCard);
	}
      else
	{
	  current_player -> equipment.off_horse = gameCard;
	  gameCard = nullptr;
	}
    }
  else if(effect == "def_horse")
    {
      if(current_player -> equipment.def_horse != nullptr)
	{
	  std::swap(current_player -> equipment.def_horse, gameCard);
	}
      else
	{
	  current_player -> equipment.def_horse = gameCard;
	  gameCard = nullptr;
	}
    }
  else if(effect.substr(0,6) == "weapon")
    {
      if(current_player -> equipment.weapon != nullptr)
	{
	  std::swap(current_player -> equipment.weapon, gameCard);
	}
      else
	{
	  current_player -> equipment.weapon = gameCard;
	  gameCard = nullptr;
	}
    }
  else if(effect.substr(0,6) == "shield")
    {
      if(current_player -> equipment.shield != nullptr)
	std::swap(current_player -> equipment.shield, gameCard);
      else
	{
	  current_player -> equipment.shield = gameCard;
	  gameCard = nullptr;
	}
    }
  else if(effect == "peach_garden")
    {
      for(Player* p : players)
	p -> modifyLife(1);
    }
  else if(effect == "acedia")
    {
      target_player -> addJudgementCard(gameCard);
      gameCard = nullptr;
    }
  else if(effect == "lightning")
    {
      target_player -> addJudgementCard(gameCard);
      gameCard = nullptr;
    }
  // else if(effect == "steal")
  // {
  // // Window* stealWindow = new Window(50,50,500,500);
  
  // }
  else
    {
      std::cout << "Card command: \"" + effect + "\" does not exist in the list" << std::endl;
    }
  
  return gameCard;
}
