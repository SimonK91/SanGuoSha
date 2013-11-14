#include "object_button.h"

#include <string>

namespace object
{

button::button(const std::string& name, int x, int y, const std::string& command_,const std::string& image, const unsigned& size)
{

	command = command_;
	active = 0;
	
	
	SDL_Surface* textSurface;
	TTF_Font* font;
	
	if(name != "")
	{
		font = TTF_OpenFont("Fonts/LHANDW.TTF", size);	
		SDL_Color textColor{0,0,0,0};
		textSurface = TTF_RenderText_Blended(font, name.c_str(), textColor);
	}
	buttonSheet = load_image(image,true); //själva knappskalet
	box.x = x;
	box.y = y;
	box.w = buttonSheet->w;
	box.h = buttonSheet->h/4;
	
	int offset = (box.h - textSurface->h)/2;
	if(name != "")
	{
		apply_surface((box.w-(textSurface->w))/2    ,offset          ,textSurface,buttonSheet); //text på alla delar av knappen
		apply_surface((box.w-(textSurface->w))/2    ,offset+box.h    ,textSurface,buttonSheet);
		apply_surface((box.w-(textSurface->w))/2 +3 ,offset+box.h*2+1,textSurface,buttonSheet);
		apply_surface((box.w-(textSurface->w))/2    ,offset+box.h*3  ,textSurface,buttonSheet);

	clean_up({textSurface},{font});	
	}
	SDL_Rect temp;
	temp.x = 0;
	temp.y = 0;
	temp.w = box.w;
	temp.h = box.h;
	clip.push_back(temp);
	
	temp.y = temp.h;
	clip.push_back(temp);
	
	temp.y = 2*temp.h;
	clip.push_back(temp);
	
	temp.y = 3*temp.h;
	clip.push_back(temp);
	
	
}

std::string button::handle_event(const SDL_Event& event)
{
    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //If the mouse is over the button
        if( inside(event) )
        {
			if(!SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1)&& active == 0){active = 1; return "";} // om muspekaren är över knappen enbart!
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 2){return "";}             // om muspekaren är över knappen och knappen är intryckt
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 3){active = 2; return "";} // om muspekaren är intryckt och går från utanför knappen till innanför
			if(active == 3){return "";}                                                           // om knappen inte är intryckt men har varit
        }
        //Om pekaren inte är över knappen
        else
        {
            //Set the button sprite
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& (active == 2 || active == 3)){active = 3;return "";} // om knappen är intryct och går utanför knappen eller fortfarande intryckt fast utanför
			else{active = 0; return "";} //annars blir knappen till neutralt värde
        }    
    }
	
	//If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
		//om vänster musknapp blev intryckt innanför knappen
        if( event.button.button == SDL_BUTTON_LEFT && inside(event) ) {active = 2; return "";}
    }
	//If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
		//om musknappen blev släppt när knappen var aktivt nertryckt
		if( event.button.button == SDL_BUTTON_LEFT && inside(event) && active == 2){active = 3; return command;}
		if( event.button.button == SDL_BUTTON_LEFT && inside(event) && active == 0){active = 1; return "";}
		if( event.button.button == SDL_BUTTON_LEFT && !inside(event)){active = 0; return "";}
    }
	return "";
}
void button::print(SDL_Surface* to_where)
{
    //Show the button
    apply_surface( box.x, box.y, buttonSheet, to_where, &clip.at(active));
}


}//slut på namnrymden