#include "object_button.h"

#include <string>

namespace object
{

button::button(std::string image, int x, int y, int w, int h)
{

	buttonSheet = load_image(image,true);
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	
	active = 0;
	
	SDL_Rect temp;
	temp.x = 0;
	temp.y = 0;
	temp.w = w;
	temp.h = h;
	clip.push_back(temp);
	
	temp.y = h;
	clip.push_back(temp);
	
	temp.y = 2*h;
	clip.push_back(temp);
	
	temp.y = 3*h;
	clip.push_back(temp);
}
bool button::inside( const pointer_arrow& arrow)
{
	return (arrow.get_x() > box.x && arrow.get_x() < box.x + box.w && arrow.get_y() > box.y && arrow.get_y() < box.y + box.h);
}
bool button::inside( const int& x, const int& y)
{
	return (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h);
}

bool button::handle_event(const SDL_Event& event, const pointer_arrow& arrow)
{
    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //If the mouse is over the button
        if( inside(arrow) )
        {
			if(!SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1)&& active == 0){active = 1; return false;} // om muspekaren är över knappen enbart!
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 2){return false;}             // om muspekaren är över knappen och knappen är intryckt
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 3){active = 2; return false;} // om muspekaren är intryckt och går från utanför knappen till innanför
			if(active == 3){return false;} // om knappen inte är intryckt men har varit
        }
        //Om pekaren inte är över knappen
        else
        {
            //Set the button sprite
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& (active == 2 || active == 3)){active = 3;return false;} // om knappen är intryct och går utanför knappen eller fortfarande intryckt fast utanför
			else{active = 0; return false;} //annars blir knappen till neutralt värde
        }    
    }
	
	//If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
		//om vänster musknapp blev intryckt innanför knappen
        if( event.button.button == SDL_BUTTON_LEFT && inside(arrow) ) {active = 2; return false;}
    }
	//If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
		//om musknappen blev släppt när knappen var aktivt nertryckt
		if( event.button.button == SDL_BUTTON_LEFT && inside(arrow) && active == 2){active = 3; return true;}
		if( event.button.button == SDL_BUTTON_LEFT && inside(arrow) && active == 0){active = 1; return false;}
		if( event.button.button == SDL_BUTTON_LEFT && !inside(arrow)){active = 0; return false;}
    }
	return false;
}
void button::print(SDL_Surface* to_where)
{
    //Show the button
    apply_surface( box.x, box.y, buttonSheet, to_where, &clip.at(active));
}

bool button::loaded()
{
	return buttonSheet != nullptr;
}

}//slut på namnrymden