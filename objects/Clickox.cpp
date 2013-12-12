#include "ClickBox.h"

#include <string>

namespace Object
{

ClickBox::Clickbox(const int& x, const int& y, const int& w, const int& h, 
					const std::string& command_)
{
	command = command_;
	active = 0;

        box.x = x;
        box.y = y;
        box.w = w;
        box.h = h;
	
}
bool Clickbox::inside( const SDL_Event& event)
{
	return (event.motion.x > box.x 
		 && event.motion.x < box.x + box.w
		 && event.motion.y > box.y
		 && event.motion.y < box.y + box.h);
}

std::string Clickbox::handleEvent(const SDL_Event& event)
{
    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //If the mouse is over the ClickBox
        if( inside(event) )
        {
			if(!SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1)&& active == 0){active = 1; return "";} // om muspekaren Ã¤r Ã¶ver knappen enbart!
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 2){return "";}             // om muspekaren Ã¤r Ã¶ver knappen och knappen Ã¤r intryckt
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& active == 3){active = 2; return "";} // om muspekaren Ã¤r intryckt och gÃ¥r frÃ¥n utanfÃ¶r knappen till innanfÃ¶r
			if(active == 3){return "";}                                                           // om knappen inte Ã¤r intryckt men har varit
        }
        //Om pekaren inte Ã¤r Ã¶ver knappen
        else
        {
            //Set the button sprite
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)&& (active == 2 || active == 3)){active = 3;return "";} // om knappen Ã¤r intryct och gÃ¥r utanfÃ¶r knappen eller fortfarande intryckt fast utanfÃ¶r
			else{active = 0; return "";} //annars blir knappen till neutralt vÃ¤rde
        }    
    }
	
	//If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
		//om vÃ¤nster musknapp blev intryckt innanfÃ¶r knappen
        if( event.button.button == SDL_BUTTON_LEFT && inside(event) ) {active = 2; return "";}
    }
	//If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
		//om musknappen blev slÃ¤ppt nÃ¤r knappen var aktivt nertryckt
		if( event.button.button == SDL_BUTTON_LEFT && inside(event) && active == 2){active = 3; return command;}
		if( event.button.button == SDL_BUTTON_LEFT && inside(event) && active == 0){active = 1; return "";}
		if( event.button.button == SDL_BUTTON_LEFT && !inside(event)){active = 0; return "";}
    }
	return "";
}
}//slut pÃ¥ namnrymden
