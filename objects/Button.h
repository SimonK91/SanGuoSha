#ifndef BUTTON_H
#define BUTTON_H

#include "Objects.h"
 #include "../functions.h"
#include <string>

namespace Object
{
class Button : public ActiveObject
{
private:
	std::vector<SDL_Rect> clip;
	SDL_Surface* button_sheet = nullptr;
	
	
public:
	
	//konstruktorer och destruktorer
	Button(const std::string& name, int x, int y, const std::string& command,
			const std::string& image, const unsigned& size);
	
	~Button(){cleanUp({button_sheet});}
	
	bool inside( const SDL_Event&);
	std::string handleEvent( const SDL_Event&);
	
	void paint(SDL_Surface*);
};

}//slut på namnrymden
#endif
