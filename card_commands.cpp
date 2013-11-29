void Game::run_effect(const std::string& effect)
{
	GameCard* card = nullptr;
	
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
	else if(effect == "attack")
	{
		target_player -> modifyLife(-1);
	}
	else
	{
		std::cout << "Card command: \"" + effect + "\" does not exist in the list" << std::endl;
	}
}