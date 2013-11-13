#ifndef checkbox_h
#define checkbox_h

#include "objects.h"
#include <string>

namespace object
{

class CheckBox : public active_object
{
private:
	bool checked = false;
	SDL_Surface* box_sheet = NULL;
	std::vector<SDL_Rect> clip;
	//bool hoverOver(SDL_Event event){return false;}
	std::string command;
	
public:
	CheckBox(int x, int y, const std::string& command, bool check = false);
	
	~CheckBox(){clean_up({box_sheet});}
	
	void print(SDL_Surface* to_where);
	
	std::string handle_event(const SDL_Event& event);
	
};

} //namespace

#endif