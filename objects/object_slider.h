#ifndef OBJECT_SLIDER_H
#define OBJECT_SLIDER_H

#include "objects.h"

#include <string>

namespace object
{
class slider : public active_object
{
private:
	SDL_Surface* bg = nullptr;
	SDL_Surface* btn = nullptr;
	SDL_Rect btn_box;
	int offset;
	int box_min;
	int box_max;

public:
	
	slider(const int& x, const int& y, const std::string& command, const int& val,
			const std::string& bg_i = "Images/Gui/thickSlider.png", const int& edge = 20,
			const std::string& btn_i = "Images/Gui/thickSliderButton.png");
	~slider();
		
	bool inside( const SDL_Event& event);
	
	std::string handle_event(const SDL_Event&);
	
	void paint(SDL_Surface* to_where);
		
protected:	
		
};
}//slut på namespace

#endif