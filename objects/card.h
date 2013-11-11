#ifndef CARD_H
#define CARD_H

#include "objects.h"

#include <iostream>

namespace object
{

class Card : public active_object
{
private:
	
protected:
	SDL_Surface* image;
public:
	Card(std::string filename);
	
	virtual ~Card(){ clean_up({image});  };
	
	void setPosition(const int& x,const int& y);
};

enum Suit
{
	clubs, heart, spades, diamond
};

enum Clan
{
	red, green, blue, gray
};

Clan str2clan(const std::string& str);
std::ostream& operator<< (std::ostream& os , Clan clan);

} //namespace 



#endif