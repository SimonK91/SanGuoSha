#include "HeroCard.h"

namespace object
{

// ID struktur:
// <maxHP> <male> <clan> <abilities>

HeroCard::HeroCard(std::string filename, std::string ID) : Card("Characters/" +filename)
{
	std::stringstream ss(ID);
	std::string strClan;
	std::string tmp;
	SDL_Rect heroClip;
	
	//setName
	name = filename.substr(0,(filename.size() - 4)); //fixas bättre så att den är generell?
	//fix rest
	ss >> maxHP;
	ss >> male;
	ss >> strClan;
	clan = str2clan(strClan);
	
	while(ss >> tmp)
	{
		abilities.push_back(tmp);
	}
}

std::string HeroCard::getAblility(unsigned index)
{ 
	if(abilities.size() > index){
		return abilities.at(index);
	}else{
		return "ERROR_INDEX_OUT_OF_BOUNDS";
	}
}

std::string HeroCard::handle_event(const SDL_Event& event)
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
			return "HeroCardInUse";		//fortfarande ett frågetecken :D
		}
	}
	return "";
}
} //namespace





