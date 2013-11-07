#ifndef card_h
#define card_h
#include "objects.h"

namespace object
{

class Card : public active_object
{
private:
	
protected:
	std::string ID;
	SDL_Surface* image;
public:
	Card() = default;
	Card(std::string identity , SDL_Surface* img) : ID(identity), image(img) {}
	virtual ~Card(){ clean_up({image});  };
	
	std::string getID(){return ID;}
};

enum Suit
{
	clubs, heart, spades, diamond
};

} //namespace 

#endif