#include "card.h"

#include <stdexcept>

namespace object
{
Card::Card(std::string filename) : active_object()
{
	image = load_image("Images/Cards/"+filename, true);
	if(!image)
		throw std::runtime_error("could not open file: Images/Cards/" +filename);
	box.w = 200;
	box.h = 282;
}

void Card::setPosition(const int& x, const int& y)
{
	box.x = x;
	box.y = y;
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