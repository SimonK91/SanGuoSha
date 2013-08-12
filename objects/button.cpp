#include "button.h"
#include <string>


button::button(std::string image, int x, int y, int w, int h)
{

	buttonSheet = load_image(image,true);
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	
	active = 0;
	
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = w;
	clip[0].h = h;
	
	clip[1].x = 0;
	clip[1].y = h;
	clip[1].w = w;
	clip[1].h = h;
	
	clip[2].x = 0;
	clip[2].y = 2*h;
	clip[2].w = w;
	clip[2].h = h;
	
	clip[3].x = 0;
	clip[3].y = 3*h;
	clip[3].w = w;
	clip[3].h = h;
	
}
bool button::inside( const pointer_arrow& arrow)
{
	return (arrow.get_x() > box.x && arrow.get_x() < box.x + box.w && arrow.get_y() > box.y && arrow.get_y() < box.y + box.h);
}
bool button::inside( const int& x, const int& y)
{
	return (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h);
}

bool button::handle_events(const SDL_Event& event, const pointer_arrow& arrow)
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
    apply_surface( box.x, box.y, buttonSheet, to_where, &clip[active] );
}