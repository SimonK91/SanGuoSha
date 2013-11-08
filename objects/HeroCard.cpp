#include "HeroCard.h"

namespace object
{

HeroCard::HeroCard(std::string filename, std::string ID) : Card(filename)
{
	// ID = ID_;	
	// SDL_Surface* img = nullptr;
	std::stringstream ss(ID);
	// std::string filename;
	
	// ss >> filename;
	// filename = "Images/Cards/" + filename;
	
	// img = load_image(filename, true);
	// if(img == nullptr)
	// {
		// //std::cout << "hej på dig din glada ping vin hej hej"  << std::endl;
		// throw std::runtime_error("could not open: " + filename);
	// }
	// image = img;
}

} //namespace