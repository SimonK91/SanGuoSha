#include "HeroCard.h"

namespace object
{

HeroCard::HeroCard(std::string filename, std::string ID) : Card(filename)
{
	std::stringstream ss(ID);
	std::string strClan;
	std::string tmp;
	SDL_Rect heroClip;
	SDL_Surface *img;
	
	ss >> maxHP;
	ss >> heroClip.x ;
	ss >> heroClip.y;
	ss >> male;
	ss >> strClan;
	clan = str2clan(strClan);
	ss >> name;
	
	while(ss >> tmp)
	{
		abilities.push_back(tmp);
	}
	
	//fixa bilder!
	heroClip.x *= (image -> w) / 9;
	heroClip.y *= (image -> h) / 5;
	heroClip.w 	= (image -> w) / 9;
	heroClip.h 	= (image -> h) / 5;
	
	img = SDL_CreateRGBSurface(0, heroClip.w, heroClip.h, 32, 0 ,0 , 0, 0);
	apply_surface(0,0, image, img, &heroClip);
	std::swap(image,img);
	clean_up({img});
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





