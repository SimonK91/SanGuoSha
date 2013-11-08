#ifndef HEROCARD_H
#define HEROCARD_H

#include "card.h"

#include <vector>
#include <sstream>
#include <stdexcept>
/*
id struktur:

<abilityID> <target_type> <range>

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
	HeroCard(std::string filename, std::string ID);
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