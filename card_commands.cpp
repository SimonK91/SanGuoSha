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
			has_window = true;
			Window* dodgeWindow = new Window(160,250,500,250);
			dodgeWindow -> makeButton("Dodge",37,70,"dodge");
			dodgeWindow -> makeButton("Take damage",260,70, "take_damage");
			add_window(dodgeWindow);
			target_player -> setCurrentPlayer(true);
			current_player -> setCurrentPlayer(false);
		}
		else
			std::cout << "no player active... :(" << std::endl;
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
	else if(effect == "steal")
	{
		if(target_player != nullptr)
		{
			Window* stealWindow = new Window(50,150,600,350);
			HeroCard* dummy = new HeroCard("back.png", "42 gray 0 dummy");

			std::vector<GameCard*> targetHand = target_player -> getHand();
			
			for(unsigned i = 0; i < targetHand.size(); ++i)
			{
				stealWindow -> addCard(new HeroCard("back.png", "42 gray 0 dummy"),100 * i, 20);
			}
			//add equipment
			if(target_player -> equipment.weapon != nullptr)
				stealWindow -> addCard(target_player -> equipment.weapon,0, 240);
			if(target_player -> equipment.shield != nullptr)
				stealWindow -> addCard(target_player -> equipment.shield, 100, 240);
			if(target_player -> equipment.off_horse != nullptr)
				stealWindow -> addCard(target_player -> equipment.off_horse, 200, 240);
			if(target_player -> equipment.def_horse != nullptr)
				stealWindow -> addCard(target_player -> equipment.def_horse, 300, 240);
			
			
			stealWindow -> makeButton("Steal",170,250, "steal_card");
			add_window(stealWindow);
			has_window = true;
		}
		else
			std::cout << "No steal... :(" << std::endl;
	}
	else if(effect == "dismantle")
	{
		if(target_player != nullptr)
		{
			Window* dismantleWindow = new Window(50,150,600,350);
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
		Window* barbarianWindow = new Window(50,350,350,200);
		
		// barbarianWindow -> addCard(gameCard,400,350);
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
		Window* arrowWindow = new Window(50,350,350,200);
		
		// barbarianWindow -> addCard(gameCard,400,350);
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
	else
	{
		std::cout << "Card command: \"" + effect + "\" does not exist in the list" << std::endl;
	}
	
	return gameCard;
}
