#include "object_click_box.h"

ClickBox::ClickBox(int xPos,int yPos, int width, int height, std::string command_)
{
	box.x = xPos;
	box.y = yPos;
	box.w = width;
	box.h = height;
	command = command_;
}

std::string ClickBox::handleEvent(const SDL_Event& event)
{
	if(inside(event) && event.type = SDL_MOUSEBUTTONDOWN)
	{
		return command;
	}
	
	
	
	
	
	return "";
}