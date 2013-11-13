#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "Objects.h"

#include <string>

namespace Object
{
class Textbox : public DeadObject
{
private:
	TTF_Font* font = nullptr;
	
	SDL_Surface* background = nullptr;
	SDL_Surface* text_area  = nullptr;
	SDL_Color text_color;
	
	std::string file_text;
	int frame_size;
	std::string font_name;
	int font_size;
	int text_counter = 0;
	int text_x;
	int text_y;
	int font_style;
	bool font_bold;
	bool font_italic;
	bool font_underlined;
	bool font_strikethrough;
	
	void setColor(std::string&);
	void applyText(const std::string&);
public:
	Textbox(const std::string& text_, const int& x, const int& y, const int& w, const int& h,
	const SDL_Color& col, const std::string& font_style, const unsigned& size);
		
	~Textbox(){cleanUp({background,text_area},{font});}
	
	void paint(SDL_Surface* to_where);
	
	void setFileText(int counter); //ej skriven
	
	void setText(const std::string&); //skrivs
};

}//namespace

#endif