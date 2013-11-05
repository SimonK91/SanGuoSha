#include "objects.h"

namespace objekt
{
class Card : public active_object
{
private:
	
protected:
	std::string ID;
	SDL_Surface* image;
public:
	Card(std::string identity , SDL_Surface* img) : ID(identity), image(img) {}
	~Card(){ /*clean_up({image});*/  };	//not intended to destruckt the image yet
	
	std::string getID(){return ID;}
};

} //namespace 