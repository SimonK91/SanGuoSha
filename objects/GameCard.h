#ifndef GAMECARD_H
#define GAMECARD_H

#include "card.h"

/*
id struktur:

<abilityID> <target_type> <range>

*/
namespace object
{

class GameCard : public Card
{
private:
	Suit suit;
	int number;
	int range;
	int target_type;
	std::string abilityID;
public:
	GameCard(int valor, Suit suit_, std::string filename, std::string ID);
	~GameCard(){}
	
	Suit getSuit(){ return suit; }
	int getNumber(){ return number; }
	
	std::string handle_event(const SDL_Event& event, const pointer_arrow& pa);
	void print(SDL_Surface* to_where){} //ska tas bort
	
	void paint(SDL_Surface* to_where)
	{
		apply_surface(box.x , box.y , image, to_where);
	}
	void paint(SDL_Surface* to_where, int x, int y)
	{
		apply_surface(x , y , image, to_where);
	}
};
} //namespace

#endif