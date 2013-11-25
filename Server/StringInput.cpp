#include "StringInput.h"


StringInput::StringInput()
{
  
  TTF_Init();
  str = "";
  text = NULL;
  
  font = TTF_OpenFont("arial.ttf", 15);
  textColor.r = 0;
  textColor.g = 0;
  textColor.b = 0;
  SDL_EnableUNICODE(SDL_ENABLE);
  
}

StringInput::~StringInput()
{
  SDL_FreeSurface(text);
  SDL_EnableUNICODE(SDL_DISABLE);
  TTF_CloseFont(font);
  TTF_Quit();
}

void StringInput::handleInput(SDL_Event& event)
{
  if(event.type == SDL_KEYDOWN)
    {
      std::string tmp = str;
      
      if(str.length() <= 100)
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
	  else if( ( event.key.keysym.unicode >= (Uint16) '!') && (event.key.keysym.unicode <= (Uint16) '?' ) )
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
      if(str != tmp)
	{
	  SDL_FreeSurface(text);

	  // text = TTF_RenderText_Solid(font, str.c_str(), textColor);
	}
    }
}


void StringInput::showAt(SDL_Surface* screen, int x, int y)
{
  SDL_Rect tmpRect;
  tmpRect.x = x;
  tmpRect.y = y;
  int maxLength = 375;
  std::string tmpStr = "";
  unsigned row = 1;
  if(str != "")
  {
    for(unsigned i = 0; i < str.size(); ++i)
      {
	tmpStr = str.at(i);
	text = TTF_RenderText_Solid(font, tmpStr.c_str(), textColor);
	SDL_BlitSurface(text, NULL, screen, &tmpRect);
	
	tmpRect.x += text->w;
	if(tmpRect.x >= maxLength)
	  {
	    tmpRect.x = 25;
	    tmpRect.y += text->h +5;
	    row++;
	  }
	if(row > 2)
	  {
	    str.pop_back();
	  } 

      }
  } 
  



}

std::string StringInput::getStr()
{
  return str;
}
void StringInput::clear()
{
  str = "";
  SDL_FreeSurface(text);
  text = TTF_RenderText_Solid(font, str.c_str(), textColor);
}
