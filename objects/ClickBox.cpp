#include "ClickBox.h"

#include <string>

namespace Object
{

ClickBox::ClickBox(const int& x, const int& y, const int& w, const int& h, 
					const std::string& command_)
{
	command = command_;
	active = 0;
	
	
	//SDL_Surface* text_surface;
	//TTF_Font* font;
	
	/*if(name != "")
	  {
	    font = TTF_OpenFont("Fonts/LHANDW.TTF", size);        
	    SDL_Color text_color{0,0,0,0};
	    text_surface = TTF_RenderText_Blended(font, name.c_str(), text_color);
	  }*/
        //ClickBox_sheet = loadImage(image,true); //själva knappskalet
        box.x = x;
        box.y = y;
        box.w = w;
        box.h = h/4;
	
	//int offset = (box.h - text_surface->h)/2;
	/*if(name != "")
	{
		applySurface((box.w-(text_surface->w))/2    ,offset          ,text_surface,ClickBox_sheet); //text pÃ¥ alla delar av knappen
		applySurface((box.w-(text_surface->w))/2    ,offset+box.h    ,text_surface,ClickBox_sheet);
		applySurface((box.w-(text_surface->w))/2 +3 ,offset+box.h*2+1,text_surface,ClickBox_sheet);
		applySurface((box.w-(text_surface->w))/2    ,offset+box.h*3  ,text_surface,ClickBox_sheet);

	cleanUp({text_surface},{font});	
	}*/
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
bool ClickBox::inside( const SDL_Event& event)
{
	return (event.motion.x > box.x 
		 && event.motion.x < box.x + box.w
		 && event.motion.y > box.y
		 && event.motion.y < box.y + box.h);
}

std::string ClickBox::handleEvent(const SDL_Event& event)
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
//void ClickBox::paint(SDL_Surface* to_where)
//{
    //Show the ClickBox
    //applySurface( box.x, box.y, ClickBox_sheet, to_where, &clip.at(active));
//}


}//slut pÃ¥ namnrymden
