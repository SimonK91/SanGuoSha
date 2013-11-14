#include "Slider.h"

#include <string>
#include <sstream>

namespace Object
{

Slider::Slider(const int& x, const int& y, const std::string& command_, const int& val,
			   const std::string& bg_i, const int& edge,
			   const std::string& btn_i)
{

	offset = edge;
	command = command_;
	
	//layout för slidern
	bg = loadImage(bg_i, true);
	box.x = x;
	box.y = y;
	box.w = bg->w;
	box.h = bg->h;
	
	//sliderknappen
	btn = loadImage(btn_i, true);
	//btn_box.x = offset;
	btn_box.y = (box.h - btn->h+1)/2;
	btn_box.w = btn->w;
	btn_box.h = btn->h;
	
	box_min = offset;
	box_max = box.w - btn_box.w - offset;
	btn_box.x = offset + (val*(box_max-offset))/100;
	
}


std::string Slider::handleEvent(const SDL_Event& event)
{
	//Hantera event
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
	    if( event.button.button == SDL_BUTTON_LEFT && inside(event) ) 
		{
			active = 1;
		}
		//return "";
	}
	if(active == 1 && (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN))
	{
		int x = event.motion.x - btn_box.w/2;// - offset + btn_box.w/2;
		if(x >= box.x + box_min && x <= box.x + box_max)
			btn_box.x = x - box.x;
		
		else if(x < box.x + box_min)
			btn_box.x = box_min;
		
		else if(x > box_max)
			btn_box.x = box_max;
		
		int value = (btn_box.x - box_min)*100/(box_max - box_min);
		return command + " " + I2S(value);	
	}
	if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		active = 0;
	}
	return "";
}



bool Slider::inside( const SDL_Event& event)
{
	int left_edge  = box.x;// + btn_box.x;
	int right_edge = left_edge + box.w;// + btn_box.w;
	int upper_edge = box.y;
	int lower_edge = upper_edge + box.h;
	
	return (event.motion.x > left_edge 
		 && event.motion.x < right_edge
		 && event.motion.y > upper_edge
		 && event.motion.y < lower_edge);
}

void Slider::paint(SDL_Surface* to_where)
{	
	
	applySurface( box.x, box.y, bg, to_where, nullptr);
	applySurface( box.x + btn_box.x,
				btn_box.y+box.y, btn, to_where, nullptr);
	
}

Slider::~Slider()
{
	cleanUp({bg, btn});
}

}//slut på namespace
