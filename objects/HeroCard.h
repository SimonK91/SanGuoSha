#ifndef HEROCARD_H
#define HEROCARD_H

#include "card.h"

#include <vector>
#include <sstream>
#include <stdexcept>
/*
id struktur:

<cardImageFileName> <abilityID> <target_type> <range>

*/
namespace object
{
class HeroCard : public Card
{
private:
	int maxHP;
	Clan clan;
	bool male;
	std::string name;
	std::vector<std::string> abilities;
public:
	HeroCard(std::string ID_)
	{
		ID = ID_;
		SDL_Surface* img = nullptr;
		std::stringstream ss(ID_);
		std::string filename = "Images/Cards/";
		std::string tmpStr;
		
		ss >> tmpStr;
		filename += tmpStr;
		
		img = load_image(filename, true);
		if(img == nullptr)
		{
			//std::cout << "hej på dig din glada ping vin hej hej"  << std::endl;
			throw std::runtime_error("could not open: " + filename);
		}
		image = img;
		
	}
	~HeroCard(){}
	
	void print(SDL_Surface* to_where){}
	void paint(SDL_Surface* to_where, int x, int y)
	{
		apply_surface(x, y, image, to_where);
	}
	bool getMale(){ return true;}
	std::string getName(){ return name; }
	std::string getAblility(int index){ return ""; }
	std::string handle_event(const SDL_Event& event, const pointer_arrow& pa){ return "";}
	Clan getClan(){ return clan; }
};

} // namespace

#endif