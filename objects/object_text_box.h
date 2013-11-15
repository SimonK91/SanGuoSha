#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "objects.h"

#include <string>

namespace object
{
class text_box : public dead_object
{
private:
	TTF_Font* font = nullptr;
	
	SDL_Surface* background = nullptr;
	SDL_Surface* textArea  = nullptr;
	SDL_Color textColor;
	
	std::string fileText;
	int frameSize;
	std::string fontName;
	int fontSize;
	int textCounter = 0;
	int textX;
	int textY;
	int fontStyle;
	bool fontBold;
	bool fontItalic;
	bool fontUnderlined;
	bool fontStrikethrough;
	
	void set_color(std::string&);
	void apply_text(const std::string&);
public:
	text_box(const std::string& text_, const int& x, const int& y, const int& w, const int& h,
	const SDL_Color& col, const std::string& font_style, const unsigned& size);
		
	~text_box(){clean_up({background,textArea},{font});}
	
	void paint(SDL_Surface* to_where);
	
	void setFileText(int counter); //ej skriven
	
	void set_text(const std::string&); //skrivs
};

}//namespace

#endif