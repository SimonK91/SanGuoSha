#include "StringInput.h"


StringInput::StringInput()
{
  
  //TTF_Init();
  str = "";
  //text = NULL;
  
  /*font = TTF_OpenFont("arial.ttf", 30);
  textColor.r = 0;
  textColor.g = 0;
  textColor.b = 0;*/
  SDL_EnableUNICODE(SDL_ENABLE);
  
}

StringInput::~StringInput()
{
  //SDL_FreeSurface(text);
  SDL_EnableUNICODE(SDL_DISABLE);
}

void StringInput::handleInput(SDL_Event& event)
{
  if(event.type == SDL_KEYDOWN)
    {
      std::string tmp = str;
      
      if(str.length() <= 30)
	{
	  //if space
	  if(event.key.keysym.unicode == (Uint16)' ')
	    {
	      str += (char)event.key.keysym.unicode;
	    }
	  //if number
	  else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
	    {
	      str += (char)event.key.keysym.unicode;
	    }
	  //if upper case
	  else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
	    {
	      str += (char)event.key.keysym.unicode;
	      }
	  //if lower case
	  else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
	    {
	      str += (char)event.key.keysym.unicode;
	    }
	}
	 //if backspace
	  if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
	    {
	      str.resize(str.length()-1);
	    }
	      
	 
      //kolla om strängen ändrats
	  /* if(str != tmp)
	{
	  SDL_FreeSurface(text);

	  text = TTF_RenderText_Solid(font, str.c_str(), textColor);
	  }*/
    }
}

/*
void StringInput::paint(SDL_Surface* screen, int x_pos, int y_pos)
{
  SDL_Rect tmpRect;
  tmpRect.x = x_pos;
  tmpRect.y = y_pos;
  if(text != NULL)
  {
      SDL_BlitSurface(text, NULL, screen, &tmpRect);
  } 
}
*/
std::string StringInput::getStr()
{
  return str;
}
void StringInput::clear()
{
  str = "";
  // SDL_FreeSurface(text);
  // text = TTF_RenderText_Solid(font, str.c_str(), textColor);
}
