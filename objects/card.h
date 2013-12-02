#ifndef CARD_H
#define CARD_H

#include "objects.h"

#include <iostream>

namespace Object
{

class Card : public ActiveObject
{
private:
	
protected:
	Surface image;

public:
	Card(std::string filename);
	
	
	std::string handleEvent(const SDL_Event& event);
	virtual ~Card() = default;
	void paint(Surface& to_where){ applySurface(box.x , box.y , image, to_where);}
	void setPosition(const int& x,const int& y);
};

enum Suit
{
	clubs, hearts, spades, diamonds
};

enum Clan
{
	red, green, blue, gray
};

Clan str2clan(const std::string& str);
std::ostream& operator<< (std::ostream& os , Clan clan);

} //namespace 



#endif
