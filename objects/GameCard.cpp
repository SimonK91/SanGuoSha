#include "gameCard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace object
{
GameCard::GameCard(int valor, Suit suit_, std::string ID_)
{
	ID = ID_;
	
	SDL_Surface* img = nullptr; //fixa bilden!
	std::stringstream ss(ID_);
	std::string filename = "Images/Cards/";
		
	std::string tmpStr;
	ss >> tmpStr;
	filename += tmpStr; // nu har vi hela sökvägen!
		
	img = load_image(filename,true); //hoppas på det bästa :D
	if(img == nullptr)
		throw std::runtime_error ("could not open image file: " + filename);
	image = img;
		
	ss >> abilityID;
	ss >> target_type;
	ss >> range;
	//detta sak ändras så att det fungerar bättre o är rätt bild!!
	img = load_image("Images/Gui/borderLeftTopCorner.png",true); //suit!
	
	if(img == nullptr)
		throw std::runtime_error ("could not open image file: Images/Gui/borderLeftTopCorner.png");
	
	apply_surface(10,10, img, image, nullptr);
	clean_up({img});
	
	//detta sak ändras så att det fungerar bättre o är rätt bild!!
	img = load_image("Images/Gui/thickSliderButton.png" , true); //nummer
	
	if(img == nullptr)
		throw std::runtime_error ("could not open image file: Images/Gui/thickSliderButton.png");
	
	apply_surface(180,10, img, image, nullptr);
	clean_up({img});
	
	
	//std::cout << "target_type: " << target_type << " abilityID: "<< abilityID << " range: " << range <<  std::endl;
}

} // namespace
