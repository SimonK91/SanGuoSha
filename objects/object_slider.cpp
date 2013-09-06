#include "object_slider.h"

#include <string>
#include <sstream>


std::string I2S(const int& i)
{
	std::stringstream ss;
	ss << i;
	std::string s = ss.str();
	return s;
}
namespace object
{

slider::slider(const int& x, const int& y, const std::string& command_,
			   const std::string& bg_i, const int& edge,
			   const std::string& btn_i)
{

	offset = edge;
	command = command_;
	
	//layout för slidern
	bg = load_image(bg_i, true);
	box.x = x;
	box.y = y;
	box.w = bg->w;
	box.h = bg->h;
	
	//sliderknappen
	btn = load_image(btn_i, true);
	btn_box.x = offset;
	btn_box.y = (box.h - btn->h+1)/2;
	btn_box.w = btn->w;
	btn_box.h = btn->h;
	
	box_min = offset;
	box_max = box.w - btn_box.w - offset;
}


std::string slider::handle_event(const SDL_Event& event, const pointer_arrow& arrow)
{
	//Hantera event
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
	    if( event.button.button == SDL_BUTTON_LEFT && inside(arrow) ) 
		{
			active = 1;
		}
		return "";
	}
	if(active == 1 && event.type == SDL_MOUSEMOTION)
	{
		int x = arrow.get_x() - btn_box.w/2;// - offset + btn_box.w/2;
		if(x >= box.x + box_min && x <= box.x + box_max)
			btn_box.x = x - box.x;
		
		else if(x < box.x + box_min)
			btn_box.x = box_min;
		
		else if(x > box_max)
			btn_box.x = box_max;
		
		int value = (btn_box.x - box_min)/(box_max - box_min)*100;
		return command + " " + I2S(value);	
	}
	if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		active = 0;
	}
	return "";
}



bool slider::inside( const pointer_arrow& arrow)
{
	int left_edge  = box.x + btn_box.x;
	int right_edge = left_edge + btn_box.w;
	int upper_edge = box.y;
	int lower_edge = upper_edge + box.h;
	
	return (arrow.get_x() > left_edge 
		 && arrow.get_x() < right_edge
		 && arrow.get_y() > upper_edge
		 && arrow.get_y() < lower_edge);
}

void slider::print(SDL_Surface* to_where)
{	
	
	apply_surface( box.x, box.y, bg, to_where, nullptr);
	apply_surface( box.x + btn_box.x,
				btn_box.y+box.y, btn, to_where, nullptr);
	
}

slider::~slider()
{
	clean_up({bg, btn});
}

}//slut på namespace
