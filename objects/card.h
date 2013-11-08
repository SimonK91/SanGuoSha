#ifndef card_h
#define card_h
#include "objects.h"

#include <stdexcept>

namespace object
{

class Card : public active_object
{
private:
	
protected:
	// std::string ID;
	SDL_Surface* image;
public:
	Card() = default;
	// Card(std::string identity , SDL_Surface* img) : ID(identity), image(img) {}
	Card(std::string filename)
	{
		image = load_image("Images/Cards/"+filename, true);
		if(image == nullptr)
			throw std::runtime_error("could not open file: Images/Cards/" +filename);
	}
	virtual ~Card(){ clean_up({image});  };
	
	// std::string getID(){return ID;}
};

enum Suit
{
	clubs, heart, spades, diamond
};

enum Clan
{
	red, green, blue, gray
};

} //namespace 

#endif