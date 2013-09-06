#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "objects.h"
#include <string>

namespace object
{

class text_box : public dead_object
{
private:
TTF_Font* font;
/*
	SDL_Rect clip;
	SDL_Color textColor;
	
	SDL_Surface* background;
	SDL_Surface* textArea ;
	std::string text;
	std::string fileText;
	int textCounter = 0;
	*/
public:
	//text_box(int a = 0){
		
	//}

/*
	text_box(const std::string& text_, const int& x, const int& y, const int& w, const int& h,
	SDL_Color col, const std::string& font_style, const unsigned& size)
		{
			text = text_;
			font = TTF_OpenFont(font_style.c_str(), size); 
			textArea = TTF_RenderText_Solid(font,text.c_str(),col);	//ska fixas så att den inte går outofbounds
			background = load_image("Images/Gui/windowBackground.png",true);	
			
			textColor = col;
			box.x = x;
			box.y = y;
			clip.x = 0;
			clip.y = 0;
			clip.w = w;
			clip.h = h;
			
		}
*/
	~text_box()
	{
		//clean_up({textArea,background},{font});
	}
	
		
	bool loaded(){return true/*font != nullptr*/;}
	
	void print(SDL_Surface* to_where)
	{/*
		textArea = TTF_RenderText_Solid(font,text.c_str(),textColor);
		apply_surface(box.x, box.y, background, to_where,&clip);
		apply_surface(box.x, box.y, textArea, to_where, &clip);	*/
	}
	/*
	int get_w(){if(background != nullptr)
					return background->w;
				return 0;}
	int get_h(){if(background != nullptr)
					return background->h;
				return 0;}
			*/	
	bool set_font(std::string font_style, int size = 12);
	
	void setText(const std::string & newText);//ej skriven
	
	void setFileText(int counter); //ej skriven
	
	void fixBackground(); //ej skriven

};

}//namespace

#endif