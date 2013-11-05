#ifndef BUTTON_H
#define BUTTON_H

#include "objects.h"
//#include "../functions.h"
#include <string>

namespace object
{
class button : public active_object
{
private:
	std::vector<SDL_Rect> clip;
	SDL_Surface* buttonSheet = nullptr;
	
	
public:
	
	//konstruktorer och destruktorer
	button(const std::string& name, int x, int y, const std::string& command,
			const std::string& image, const unsigned& size);
	
	~button(){clean_up({buttonSheet});}
	
	bool inside( const SDL_Event&);
	std::string handle_event( const SDL_Event&);
	
	void print(SDL_Surface*);
};

}//slut på namnrymden
#endif