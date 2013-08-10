#include "button.h"
#include <string>


button::button(std::string image, int x, int y, int w, int h)
{

	buttonSheet = load_image(image,255,255,255);
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	
	active = 1;
	
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

void button::handle_events(const SDL_Event& event, const pointer_arrow& arrow)
{

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        
        //If the mouse is over the button
        if( inside(arrow) )
        {
            //Set the button sprite
            active = 1;
        }
        //If not
        else
        {
            //Set the button sprite
            active = 0;
        }    
    }
	//If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
          
            //If the mouse is over the button
            if( inside(arrow) )
            {
                //Set the button sprite
                active = 2;
            }
        }
    }
	//If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        { 
            
            //If the mouse is over the button
            if( inside(arrow) )
            {
                //Set the button sprite
                active = 3;
            }
        }
    }
}
void button::show(SDL_Surface* to_where)
{
    //Show the button
    apply_surface( box.x, box.y, buttonSheet, to_where, &clip[active] );
}