bool Game::ruleTargetOK(Player* target)
{
	if(selected_card == nullptr)
		return false;

	if(target -> getLife() <= 0)
		return false;

	int distance = getDistance(current_player, target);
	
	int weapon_range = 1;
	{ // fixar weapon range
		if(current_player->equipment.weapon != nullptr)
		{
			weapon_range = current_player->equipment.weapon -> getRange();
		}
	}
	
	
	 //0 = self/activated
	if(selected_card -> getTargetType() == 0)
		return false;
		
	 //5 = equipment	
	if(selected_card -> getTargetType() == 5)
		return false;
		
	 //1 = target player
	if(selected_card -> getTargetType() == 1)
	{
		if(selected_card -> getRange() == 0)  //0 = unlimited
			return true;
		else if(selected_card -> getRange() > 0 && selected_card ->getRange() < 10) //1-9 = 1-9
			return distance <= selected_card -> getRange();
		else if(selected_card -> getRange() == 10)  //10 = weapon range
			return distance <= weapon_range;	
	}
	
	
	if(selected_card -> getAbility() == "duress")
	{
		if(target_player == nullptr)
		{
			if(target -> equipment.weapon != nullptr)
				return true;
		}
		else if(source_player == nullptr)
		{
			distance = getDistance(target_player,target);
			if(target -> equipment.weapon -> getRange() >= distance)
				return true;
		}
	}
				
	
	
	return false;
}

bool Game::rulePlayCardOK()
{
	std::cout << "selected_card == nullptr: " << std::boolalpha << (selected_card == nullptr) << std::endl;
	std::cout << "selected_card == nullptr: " << std::boolalpha << (selected_card == nullptr) << std::endl;
	if(selected_card == nullptr)
		return false;
	
	if(selected_card -> getAbility() == "peach" && current_player -> getLife() != current_player -> getMaxLife())
		return false;
		
		
	if(selected_card -> getTargetType() == 0 || selected_card -> getTargetType() == 5)
		return true;
		
		
	if(selected_card -> getTargetType() == 1 && target_player != nullptr)
		return true;
		
	if(selected_card -> getAbility() == "duress" && target_player != nullptr && source_player != nullptr)
		return true;
		
	return false;
}