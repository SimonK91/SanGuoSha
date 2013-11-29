#ifndef CLICKBOX_H
#define CLICKBOX_H

#include "Objects.h"
 #include "../functions.h"
#include <string>

namespace Object
{
class ClickBox : public ActiveObject
{
private:
	std::vector<SDL_Rect> clip;
	//SDL_Surface* button_sheet = nullptr;
	
	
public:
	
	//konstruktorer och destruktorer
	ClickBox(const int& x, const int& y, const int& w, const int& h, const std::string& command);
	
	~ClickBox(){/*cleanUp({button_sheet});*/}
	
	bool inside( const SDL_Event&);
	std::string handleEvent( const SDL_Event&);
	
	void paint(SDL_Surface*){}
};

}//slut på namnrymden
#endif
