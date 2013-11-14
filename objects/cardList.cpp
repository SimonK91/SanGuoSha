#include "cardList.h"
#include "gameCard.h"
#include "heroCard.h"
	
#include <algorithm>
#include <chrono>
#include <stdexcept>

namespace object
{

CardList::CardList(const std::string& setting)
{
	image = load_image("Images/Cards/back.png", true);
	if(!image)
		throw std::runtime_error("could not open imageFile: Images/Cards/back.png");
	
	if(setting == "card_deck")
		loadCardDeck();
	else if(setting == "hero_deck")
		loadHeroDeck();
	else
		throw std::runtime_error("no such deck type as: " + setting);
	
	shuffle(); //blanda listan fint^^
}
	
CardList::~CardList()
{
	clean_up({image}); 
		
	while(!set.empty())
	{
		delete set.back();
		set.pop_back(); //??? fungerar detta? eller fuckas det upp med pekare? testa det vet ja :) 
	}
}
	
Card* CardList::drawCard()
{
	Card* c = set.front();
	set.front() = nullptr; //peka bort så att vi inte tar bort c ^^
	set.erase(set.begin());
	return c;
}
	
void CardList::pushBottom(Card* card)
{
	set.push_back(card);
	card = nullptr;
}
	
void CardList::pushTop(Card* card)
{
	set.insert(set.begin(), card);
	card = nullptr; 
}
	
void CardList::shuffle()
	{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle (set.begin(), set.end(), std::default_random_engine(seed));
}

//kolla inte här nere... du blir bara ledsen :'(

void CardList::loadHeroDeck()
{
	//gameCard( number, suit, filename, ability targetType range );
	// set.push_back(new GameCard(1,heart,"chi_tu.png","attack 1 0"));
	
}

void CardList::loadCardDeck()
{
	
}

} //namespace