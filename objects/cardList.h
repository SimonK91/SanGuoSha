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
    Surface image;
    std::vector<Card*> set;
    unsigned seed;
    
    void loadCardDeck();
    void loadHeroDeck();
  public:
    CardList(const std::string& setting);
    CardList() = default;
    ~CardList();
    
    Card* drawCard();
    unsigned getSeed(){ return seed; }
    void pushBottom(Card* card);
    void pushTop(Card* card);
    void shuffle(unsigned s = 0);
    bool empty();   
    int size(){return set.size();}   
    void paint(Surface& to_where)
	{
		applySurface(0, 0, image, to_where);
	} //WTF!	
  };  
} //namespace
#endif
