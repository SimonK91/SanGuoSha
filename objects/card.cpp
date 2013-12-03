#include "card.h"

#include <stdexcept>

namespace Object
{
Card::Card(std::string filename) : ActiveObject()
{
	image = loadImage("Images/Cards/"+filename, true);
	image.setName(filename.substr(0,filename.size()-4));
	if(!image.getImage())
		throw std::runtime_error("could not open file: Images/Cards/" +filename);
	box.w = image -> w;
	box.h = image -> h;
}

void Card::setPosition(const int& x, const int& y)
{
	box.x = x;
	box.y = y;
}
std::string Card::handleEvent(const SDL_Event& event)
{
	//ska fixas mer så att den går att använda på något vettigt sätt :D
	if(event.type == SDL_MOUSEBUTTONUP)
	{
		if(active == 1)
		{
			active = 0;
			box.y += 20;
			//return abilityID;
		}
		else if(active == 0 && event.motion.x > box.x && event.motion.x < box.x + box.w && event.motion.y > box.y && event.motion.y < box.y + box.h)
		{
			active = 1;
			box.y -= 20;
			return "activated";
		}
	}
	return "";
}

Clan str2clan(const std::string& str)
{
	if(str == "red"){
		return red;
	}else if(str == "green"){
		return green;
	}else if(str == "blue"){
		return blue;
	}else if(str == "gray"){
		return gray;
	}else {
		throw std::runtime_error("Clan: " + str + " is not a clan!");
	}
}

std::ostream& operator<< (std::ostream& os , Clan clan)
{
	switch(clan)
	{
		case red:
			os << "red";
			break;
		case green:
			os << "green";
			break;
		case blue:
			os << "blue";
			break;
		case gray:
			os << "gray";
			break;
		default:
			os << "undefined clan";
	}
	return os;
}

} //namespace
