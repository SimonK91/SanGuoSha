#include "HeroCard.h"

namespace object
{

HeroCard::HeroCard(std::string filename, std::string ID) : Card(filename)
{
	std::stringstream ss(ID);
	std::string strClan;
	std::string tmp;

	ss >> maxHP;
	ss >> strClan;
	clan = str2clan(strClan);
	ss >> male;
	ss >> name;
	
	while(ss >> tmp)
	{
		abilities.push_back(tmp);
	}
}

std::string HeroCard::getAblility(int index)
{ 
	if(abilities.size() > index){
		return abilities.at(index);
	}else{
		return "ERROR INDEX OUT OF BOUNDS";
	}
}

std::string HeroCard::handle_event(const SDL_Event& event, const pointer_arrow& pa)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(active == 1)
		{
			active = 0;
			box.y += 20;
		}
		else if(active == 0 && event.motion.x > box.x && event.motion.x < box.x + box.w && event.motion.y > box.y && event.motion.y < box.y + box.h)
		{
			active = 1;
			box.y -= 20;
			return "HeroCardInUsed";		//fortfarande ett frågetecken :D
		}
	}
	return "";
}
} //namespace





