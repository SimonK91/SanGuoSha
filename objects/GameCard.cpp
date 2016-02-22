#include "GameCard.h"
#include <string>
#include <sstream>
#include <stdexcept>

namespace Object
{
  GameCard::GameCard(int valor, Suit suit_, std::string filename, std::string ID) : Card(filename), suit(suit_), number(valor)
  {	
    Surface img;
    std::stringstream ss(ID);
    SDL_Rect suitClip;
    int imageOffset;
    
    ss >> abilityID;
    ss >> target_type;
    ss >> range;
    //detta sak ändras så att det fungerar bättre o är rätt bild!!
    img = loadImage("Images/Cards/suit.png",true); //suit!
    
    if(!img.getImage())
      throw std::runtime_error ("could not open image file: Images/Card/suits.png");
    
    imageOffset = (img -> h) / 2;
    switch(suit)
      {
      case hearts:
	suitClip.x = 0;
	suitClip.y = 0;
	break;
      case clubs:
	suitClip.x = imageOffset;
	suitClip.y = imageOffset;
	break;
      case spades:
	suitClip.x = 0;
	suitClip.y = imageOffset;
	break;
      case diamonds:
	suitClip.x = imageOffset;
	suitClip.y = 0;
	break;
      default:
	throw std::runtime_error("no suit avilable!");
      }
    suitClip.w = imageOffset;
    suitClip.h = imageOffset;
    
    applySurface(13,27, img, image, &suitClip);    
    img = loadImage("Images/Cards/numbers.png" , true); //nummer
    
    if(!img.getImage())
      throw std::runtime_error ("could not open image file: Images/Gui/numbers.png"); //bilden är inte bra än...
    
    // fixa med suitClip som återanvänds för numrett
    suitClip.w = img -> w / 2 ;
    suitClip.h = img -> h / 13;
    suitClip.y =  suitClip.h * (valor - 1);
    
    if(suit == hearts || suit == diamonds)
      suitClip.x = img -> w / 2;
    else
      suitClip.x = 0;
    
    applySurface(13,8, img, image, &suitClip);

    description->setFileText("Data/card_descriptions.txt", abilityID );
   
  }
} // namespace
