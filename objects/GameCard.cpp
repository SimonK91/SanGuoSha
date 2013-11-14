#include "gameCard.h"
#include <string>
#include <sstream>
#include <stdexcept>

namespace object
{
GameCard::GameCard(int valor, Suit suit_, std::string filename, std::string ID) : Card(filename), suit(suit_), number(valor)
{	
	SDL_Surface* img = nullptr; //fixa bilden!
	std::stringstream ss(ID);
	SDL_Rect suitClip;
	int imageOffset;
		
	ss >> abilityID;
	ss >> target_type;
	ss >> range;
	//detta sak ändras så att det fungerar bättre o är rätt bild!!
	img = load_image("Images/Cards/suit.png",true); //suit!
	
	if(!img)
		throw std::runtime_error ("could not open image file: Images/Card/suits.png");
	
	imageOffset = (img -> h) / 2;
	switch(suit)
	{
		case heart:
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
		case diamond:
			suitClip.x = imageOffset;
			suitClip.y = 0;
			break;
		default:
			throw std::runtime_error("no suit avilable!");
	}
	suitClip.w = imageOffset;
	suitClip.h = imageOffset;
	
	apply_surface(13,27, img, image, &suitClip);
	
	clean_up({img});
	
	img = load_image("Images/Cards/numbers.png" , true); //nummer
	
	if(!img)
		throw std::runtime_error ("could not open image file: Images/Gui/numbers.png"); //bilden är inte bra än...
		
	// fixa med suitClip som återanvänds för numrett
	suitClip.w = img -> w / 2 ;
	suitClip.h = img -> h / 13;
	suitClip.y =  suitClip.h * (valor - 1);
	
	if(suit == heart || suit == diamond)
		suitClip.x = img -> w / 2;
	else
		suitClip.x = 0;
			
	apply_surface(13,7, img, image, &suitClip);
	clean_up({img});
}

std::string GameCard::handle_event(const SDL_Event& event, const pointer_arrow& pa)
{
	//ska fixas mer så att den går att använda på något vettigt sätt :D
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(active == 1)
		{
			active = 0;
			box.y += 20;
			return abilityID;
		}
		else if(active == 0 && event.motion.x > box.x && event.motion.x < box.x + box.w && event.motion.y > box.y && event.motion.y < box.y + box.h)
		{
			active = 1;
			box.y -= 20;
			return "gameCardInUse";
		}
	}
	return "";
}

} // namespace
