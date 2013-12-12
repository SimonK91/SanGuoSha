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
	
	if(selected_card -> getAbility() == "attack")
	{
		if(has_attacked)
			return false;
		if((current_player -> equipment.weapon) != nullptr && (current_player -> equipment.weapon) -> getAbility() == "weapon7" && (current_player -> getHand()).size() == 1)
		{
			while(target_player.size() >= 3)
			{
				target_player.at(0) -> setSelected(false);
				target_player.erase(target_player.begin());
			}
			if(target -> getSelected())
				return false;
		}
		else
		{
			while(target_player.size() >= 1)
			{
				target_player.at(0) -> setSelected(false);
				target_player.erase(target_player.begin());
			}
		}
		return distance <= weapon_range;
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
		{
			
			while(target_player.size() >= 3)
			{
				target_player.at(0) -> setSelected(false);
				target_player.erase(target_player.begin());
			}
			
			return true;
		}
		else if(selected_card -> getRange() > 0 && selected_card ->getRange() < 10) //1-9 = 1-9
		{
			while(target_player.size() >= 1)
			{
				target_player.at(0) -> setSelected(false);
				target_player.erase(target_player.begin());
			}
			return distance <= selected_card -> getRange();
		}
		else if(selected_card -> getRange() == 10)  //10 = weapon range
		{
			while(target_player.size() >= 1)
			{
				target_player.at(0) -> setSelected(false);
				target_player.erase(target_player.begin());
			}
			return distance <= weapon_range;	
		}
	}
	
	
	if(selected_card -> getAbility() == "duress")
	{
		if(target_player.size() == 0)
		{
			if(target -> equipment.weapon != nullptr)
				return true;
		}
		else if(target_player.size() == 1)
		{
			distance = getDistance(target_player.at(0),target);
			if(target_player.at(0) -> equipment.weapon -> getRange() >= distance)
				return true;
		}
	}
	if(selected_card -> getAbility() == "acedia")
	{
		if(!target -> hasAcedia())
			return true;
	}
				
	
	
	return false;
}

bool Game::rulePlayCardOK()
{
	if(selected_card == nullptr)
		return false;
	
	if(selected_card -> getAbility() == "heal" && current_player -> getLife() == current_player -> getMaxLife())
		return false;
		
	if(selected_card -> getAbility() == "lightning" && current_player -> hasLightning())
		return false;
		
	if(selected_card -> getTargetType() == 0 || selected_card -> getTargetType() == 5)
		return true;
		
		
	if(selected_card -> getTargetType() == 1 && target_player.at(0) != nullptr)
		return true;
		
	if(selected_card -> getAbility() == "duress" && target_player.size() == 2)
		return true;
		
	return false;
}

int  Game::ruleWinCondition()
{
	int rebel = 0;
	int loyal = 0;
	int spy = 0;
	int emperor = 0;
	for(auto p : players)
	{
		if(p -> isAlive())
		{
			if( p ->getRole() == 0)
				++emperor;
			else if( p ->getRole() == 1)
				++loyal;
			else if( p ->getRole() == 2)
				++spy;
			else if( p ->getRole() == 3)
				++rebel;
		}
	}
	if(emperor != 0 && rebel == 0 && spy == 0)
		return 1; // Emperor victory
	
	if(emperor == 0)
	{
		if(loyal == 0 && rebel == 0 && spy == 1)
			return 2; //spy victory
		else if(rebel != 0)
			return 3; //rebel victory
		else
			return 4; //no victor
	}
	
	return 0;
}