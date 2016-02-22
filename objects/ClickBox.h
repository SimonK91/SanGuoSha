#ifndef CLICKBOX_H
#define CLICKBOX_H

#include "Objects.h"
#include "../Functions.h"
#include <string>

namespace Object
{
class Clickbox : public ActiveObject
{
private:
	std::vector<SDL_Rect> clip;
	//SDL_Surface* button_sheet = nullptr;
	
	
public:
	
	//konstruktorer och destruktorer
	Clickbox(const int& x, const int& y, const int& w, const int& h, const std::string& command);
	
	~Clickbox(){/*cleanUp({button_sheet});*/}
	
	bool inside( const SDL_Event&);
	std::string handleEvent( const SDL_Event&);
	
	void paint(Surface&){};
};

}//slut på namnrymden
#endif
