#ifndef CARDLIST_H
#define CARDLIST_H

#include "GameCard.h"
#include "HeroCard.h"
#include <vector>

namespace Object
{
class CardList
{
private:
	SDL_Surface* image;
	std::vector<Card*> set;
	void loadCardDeck();
	void loadHeroDeck();
public:
	CardList(const std::string& setting);
	~CardList();
	
	Card* drawCard();
	void pushBottom(Card* card);
	void pushTop(Card* card);
	void shuffle();
	bool empty();
	
	void paint(SDL_Surface* to_where)
	{
		applySurface(0, 0, image, to_where);
	} //WTF!!
	
};

} //namespace

#endif