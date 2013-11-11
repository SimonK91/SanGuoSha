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
	//om du klickas på aktiviera
	//om klicka annat och du är aktivierad skicka ability! eller dylikt
	//annars... inte något
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		
		if(event.motion.x > box.x && event.motion.x < box.x + box.w && event.motion.y > box.y && event.motion.y < box.y + box.h)
		{
			active = 1;
			std::cout << "the card is active" << std::endl;
		}
		else
		{
			std::cout << "card is inactive" << std::endl;
			active = 0;
		}
		
		// if(active)
		// {
			// //gör grejer :D
			// active = 0;
			// return "ability";
		// }
		
	}
	
	return "";
	
}
} //namespace





