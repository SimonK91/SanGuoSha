#include "object_text_box.h"
#include <sstream>
#include <vector>
#include <queue>
namespace object
{
text_box::text_box(const std::string& text_, const int& x, const int& y, const int& w, const int& h,
	const SDL_Color& col, const std::string& font_style, const unsigned& size)
{
	
	//fixar bakgrundsbilden
	background = load_image("Images/Gui/windowBackground.png",true);
	SDL_Surface* tmp_bg;
	
	//övre ramen
	tmp_bg = load_image("Images/Gui/window/tb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	frameSize = tmp_bg->h;
	clean_up({tmp_bg});
	//vänstra ramen
	tmp_bg = load_image("Images/Gui/window/lb.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre ramen
	tmp_bg = load_image("Images/Gui/window/bb.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//högra ramen
	tmp_bg = load_image("Images/Gui/window/rb.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//övre vänstra hörnet
	tmp_bg = load_image("Images/Gui/window/ltc.png",true);
	apply_surface(0,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//övre högra hörnet
	tmp_bg = load_image("Images/Gui/window/rtc.png",true);
	apply_surface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre vänstra hörnet
	tmp_bg = load_image("Images/Gui/window/lbc.png",true);
	apply_surface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	//nedre högra hörnet
	tmp_bg = load_image("Images/Gui/window/rbc.png",true);
	apply_surface(w - tmp_bg->w, h - tmp_bg->h, tmp_bg, background, nullptr);
	clean_up({tmp_bg});
	
	//öppnar fonten
	
	fontSize = size;
	fontName = font_style;
	font = TTF_OpenFont(fontName.c_str(), fontSize); 
	textColor = col;
	fontBold = false;
	fontStyle = 0;
	fontItalic = 0;
	fontUnderlined = 0;
	fontStrikethrough = 0;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	clip.x = 0;
	clip.y = 0;
	clip.w = w;
	clip.h = h;
	
	set_text(text_);	

}
		
void text_box::print(SDL_Surface* to_where)
	{
		//apply_surface(box.x, box.y, background, to_where, &clip);
		apply_surface(box.x, box.y, textArea, to_where, &clip);
	}


void text_box::set_color(std::string& color)
{
	color.erase(0,3);				//tar bort de första tecknena ("<|c")		
	color.resize(color.size()-1);	//tar bort det sista tecknet (dvs '>')
	if(color.size() != 6)			//kontrollerar så att det finns 6 tecken kvar (0-255 i hex)
		return;						//om inte, gå ut
		
	std::stringstream ss(color);	//mata in strängen i stringstream
	
	std::vector<Uint8> tmp;			//skapa en vektor för att lagra värdet på varje tecken
	
	for(Uint8 temp ; ss >> temp;)	//sparar värdet i ett temporärt ställe för att direkt pushas in i vektorn
	{
		tmp.push_back(temp);						//pushas in
		if(tmp.back() >= '0' && tmp.back() <= '9')			//om tecknet är mellan 0-9, ge värdet 0-9
			tmp.back() = tmp.back() - '0';
		else if(tmp.back() >= 'a' && tmp.back() <= 'f')		//om tecknet är mellan a-f, ge värdet 10-15
			tmp.back() = tmp.back() - 'a' + 10;
		else if(tmp.back() >= 'A' && tmp.back() <= 'F')		//om tecknet är mellan A-F, ge värdet 10-15
			tmp.back() = tmp.back() - 'A' + 10;
		else
			return;									// annars är tecknet ogiltligt och funktionen avbryts
	}
	Uint8 r = tmp[0]*16 + tmp[1];					//lagra de två första bitarna i "röd färg",
	Uint8 g = tmp[2]*16 + tmp[3];					//----grön färg
	Uint8 b = tmp[4]*16 + tmp[5];					//-----blå färg
	textColor = SDL_Color{r,g,b,0};					//sätt "textColor" till de nya värdena
}

void text_box::apply_text(const std::string& what_text)
{
	SDL_Surface* tmp_surface;
	std::string tmp_word;
	tmp_surface = TTF_RenderText_Blended(font,what_text.c_str(),textColor);	//skapa en yta med ordet
			
	if(textX + tmp_surface->w >= box.w - frameSize)								//om ordet inte får plats på den nuvarande raden		
	{
		textX = frameSize;														//positionera x till början på raden
		textY += 24;															//positionera y till nästa rad
	}
	
	apply_surface(textX,textY, tmp_surface, textArea, nullptr);					//skriv ut den på ytan
	
	textX += tmp_surface->w-4;													//ompositionera var nästa ord ska starta
				
	clean_up({tmp_surface});													//rensa den temporära ytan med ordet och starta på punkt (1).
}

void text_box::set_text(const std::string& what_text)
{
	if(textArea != nullptr)
	{
		clean_up({textArea});				//tömmer den nuvarande ytan om det redan fanns en
	}
	//Skapar yta att skriva på
	textArea = SDL_CreateRGBSurface(0,clip.w,clip.h,32,0,0,0,1);	//skapar en ny tom yta
	//apply_surface(0,0, load_image("Images/Gui/transparent.png",true),textArea,&clip);
	apply_surface(0,0, background, textArea, &clip);				//ritar ut bakgrunden (ramen)
	
	//laddar variabler
	std::queue<std::string> string_queue;
	textX=frameSize;					//positionera ut startposition x-led
	textY=frameSize;					//positionera ut startposition y-led
	fontStyle = 0;
	fontBold = false;
	fontItalic = false;
	fontUnderlined = false;
	fontStrikethrough = false;
	std::size_t found = 0;
	std::size_t last= 0;
	while(found != std::string::npos && !what_text.empty())          										//(1)så länge som det fortfarande finns ord att skriva ut
	{	
		found = what_text.find_first_of("< ",last);
		
		if(found == last)
		{
			if(what_text.substr(found,1) == " ")
			{
				found = what_text.find_first_not_of(" ",last);
				string_queue.push(what_text.substr(last,found-last));
				last = found;
			}
			else
			{
				found = what_text.find_first_of(">",found);
				string_queue.push(what_text.substr(last,found+1-last));
				last = found+1;
			}
		}
		else if(found != std::string::npos)
		{
			string_queue.push(what_text.substr(last,found-last));
			last = found;
		}
		else
		{
			string_queue.push(what_text.substr(last,what_text.size()-last));
		}
	}
	while(!string_queue.empty())
	{
		std::string tmp_word = string_queue.front();
		string_queue.pop();
	
		if(tmp_word.substr(0,1) == " ")
		{
			textX += tmp_word.size()*5;
		}
		if(tmp_word.substr(0,1) != "<")
		{
			apply_text(tmp_word);
		}
		else if((tmp_word == "<n>" || tmp_word == "<\n>" || tmp_word == "<newline>"))
		{
			textX = frameSize;														//positionera x till början på raden
			textY += 24;			
		}
		else if((tmp_word == "<b>" || tmp_word == "<bold>") && !fontBold)
		{
			fontBold = true;
			fontStyle += TTF_STYLE_BOLD;
			TTF_SetFontStyle(font, fontStyle);				
		}
		else if((tmp_word == "</b>" || tmp_word == "</bold>") && fontBold)
		{
			fontBold = false;
			fontStyle -= TTF_STYLE_BOLD;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "<i>" || tmp_word == "<italic>") && !fontItalic)
		{
			fontItalic = true;
			fontStyle += TTF_STYLE_ITALIC;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "</i>" || tmp_word == "</italic>") && fontItalic)
		{
			fontItalic = false;
			fontStyle -= TTF_STYLE_ITALIC;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "<u>" || tmp_word == "<underlined>") && !fontUnderlined)
		{
			fontUnderlined = true;
			fontStyle += TTF_STYLE_UNDERLINE;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "</u>" || tmp_word == "</underlined>") && fontUnderlined)
		{
			fontUnderlined = false;
			fontStyle -= TTF_STYLE_UNDERLINE;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "<s>" || tmp_word == "<strikethrough>") && !fontStrikethrough)
		{
			fontStrikethrough = true;
			fontStyle += TTF_STYLE_STRIKETHROUGH;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if((tmp_word == "</s>" || tmp_word == "</strikethrough>") && fontStrikethrough)
		{
			fontStrikethrough = false;
			fontStyle -= TTF_STYLE_STRIKETHROUGH;
			TTF_SetFontStyle(font,fontStyle);
		}
		else if(tmp_word.find("<c|",0,3) != std::string::npos)
		{
			set_color(tmp_word);
		}
		else if(tmp_word == "</c>")
		{
			tmp_word = "<c|ffffff>";
			set_color(tmp_word);
		}
	}
}

	
}//namespace