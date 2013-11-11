#include "gameCard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace object
{
GameCard::GameCard(int valor, Suit suit_, std::string filename, std::string ID) : Card(filename)
{	
	SDL_Surface* img = nullptr; //fixa bilden!
	std::stringstream ss(ID);
		
	ss >> abilityID;
	ss >> target_type;
	ss >> range;
	//detta sak ändras så att det fungerar bättre o är rätt bild!!
	img = load_image("Images/Gui/borderLeftTopCorner.png",true); //suit!
	
	if(!img)
		throw std::runtime_error ("could not open image file: Images/Gui/borderLeftTopCorner.png");
	
	apply_surface(10,10, img, image, nullptr);
	clean_up({img});
	
	//detta sak ändras så att det fungerar bättre o är rätt bild!!
	img = load_image("Images/Gui/thickSliderButton.png" , true); //nummer
	
	if(!img)
		throw std::runtime_error ("could not open image file: Images/Gui/thickSliderButton.png");
	
	apply_surface(180,10, img, image, nullptr);
	clean_up({img});
	
}

std::string GameCard::handle_event(const SDL_Event& event, const pointer_arrow& pa)
{
	//ska fixas mer så att den går att använda på något vettigt sätt :D
	return ""; 
}

} // namespace
