#ifndef HEROCARD_H
#define HEROCARD_H

#include "card.h"

#include <vector>
#include <sstream>
/*
id struktur:
<maxHP> <x,y> <male> <clan> <name> <abilities>

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
	
	//void print(SDL_Surface* to_where){}
	void paint(SDL_Surface* to_where)
	{
		apply_surface(box.x, box.y, image, to_where);
	}
	std::string getAblility(unsigned index);
	std::string handle_event(const SDL_Event& event);

	std::string getName(){ return name; }
	Clan getClan(){ return clan; }
	bool getMale(){ return male; }
	
};

} // namespace

#endif