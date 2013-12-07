#ifndef HEROCARD_H
#define HEROCARD_H

#include "card.h"
#include <vector>
#include <sstream>

namespace Object
{
  class HeroCard : public Card
  {
  private:
    int maxHP;
    Clan clan;
    bool male;
    std::string name;
    std::string file;
    std::vector<std::string> abilities;
  public:
    HeroCard(std::string filename, std::string ID);
    ~HeroCard(){}
    
    std::string getAblility(unsigned index);        
    std::string getName(){ return name; }
    std::string getFileName(){ return file; }
    int getHP()   { return maxHP;}
    Clan getClan(){ return clan; }
    bool getMale(){ return male; }	
  };
  
} // namespace
#endif
