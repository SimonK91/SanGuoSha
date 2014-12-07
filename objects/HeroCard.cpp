#include "HeroCard.h"

namespace Object
{

  HeroCard::HeroCard(std::string filename, std::string ID) : Card("Characters/" + filename)
  {
    std::stringstream ss(ID);
    std::string strClan;
    std::string tmp;
    
    ss >> maxHP;
    ss >> strClan;
    clan = str2clan(strClan);
    ss >> male;
    ss >> name;
    file = filename;
    
    while(ss >> tmp)
      {
	abilities.push_back(tmp);
      }
    description->setFileText("Data/card_descriptions.txt", name );
  }
  
  std::string HeroCard::getAblility(unsigned index)
  { 
    if(abilities.size() > index){
      return abilities.at(index);
    }else{
      return "ERROR_INDEX_OUT_OF_BOUNDS";
    }
  }
} //namespace





