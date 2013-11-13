#ifndef checkbox_h
#define checkbox_h

#include "Objects.h"
#include <string>

namespace Object
{

class Checkbox : public ActiveObject
{
private:
	bool checked = false;
	SDL_Surface* box_sheet = NULL;
	std::vector<SDL_Rect> clip;
	bool hover_over(SDL_Event event){return false;}
	std::string command;
	
public:
	Checkbox(int x, int y, const std::string& command, bool check = false);
	
	~Checkbox(){cleanUp({box_sheet});}
	
	void paint(SDL_Surface* to_where);
	
	std::string handleEvent(const SDL_Event& event);
	
};

} //namespace

#endif
