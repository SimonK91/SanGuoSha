#include "object_text_box.h"

namespace object
{

bool text_box::set_font(std::string font_style, int size)
{
	TTF_Font* temp = nullptr;
	temp = TTF_OpenFont(font_style.c_str(), size);
	if(temp == nullptr)
		return false;
	clean_up({},{font});
	font = temp;
	return true;
}
	
}//namespace