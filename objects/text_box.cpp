#include "text_box.h"

bool text_box::set_font(std::string font_style, int size = 12)
	{
		TTF_Font* temp = nullptr;
		temp = TTF_OpenFont(font_style.c_str(), size);
		if(temp == nullptr)
			return false;
		clean_up({},{font});
		font = temp;
		return true;
	}