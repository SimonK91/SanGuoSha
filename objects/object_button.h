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
			const std::string& image = "Images/Gui/cleanButton2.png");
	
	~button(){clean_up({buttonSheet});}
	
	bool inside( const pointer_arrow&);
	std::string handle_event( const SDL_Event&, const pointer_arrow&);
	bool loaded();
	
	void print(SDL_Surface*);
};

}//slut på namnrymden
#endif