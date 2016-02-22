#ifndef GAMECARD_H
#define GAMECARD_H

#include "Card.h"
#include "PopupText.h"
/*
  id struktur:

  <abilityID> <target_type> <range>
  
  target_type:0 = self
  1 = target
  2 = pending?
  3 = special
  4 = ?
  5 = equipment
  
  range:		
  0    = inf
  1->9 = const
  10   = physical
*/
namespace Object
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
    int getRange(){ return range; }
    int getTargetType(){ return target_type; }
    std::string getAbility(){ return abilityID; }    
  };
} //namespace
#endif
