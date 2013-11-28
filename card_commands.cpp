
	else if(what_command == "draw2")
	{
		for(Player* p: players)
		{
			if(p -> isCurrentPlayer())
			{	
				GameCard* card = dynamic_cast<GameCard*>(card_deck -> drawCard());
				p -> recieveCard(card);
			
				card = dynamic_cast<GameCard*>(card_deck -> drawCard());
				p -> recieveCard(card);
			}
		}
	}