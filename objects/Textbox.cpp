#include "Textbox.h"
#include <sstream>
#include <vector>
#include <queue>

namespace Object
{
  Textbox::Textbox(const int& x, const int& y, const int& w, const int& h,
		   const std::string& style, const unsigned& size) : background("textbox background"),textArea("textArea")
  {
    background = loadImage("Images/Gui/windowBackground.png",true);
    Surface tmp_bg("tmp_bg");
    
    //övre ramen
    tmp_bg = loadImage("Images/Gui/Window/tb.png",true);
    applySurface(0,0, tmp_bg, background, nullptr);
    frame_size = tmp_bg->h;
    //vänstra ramen
    tmp_bg = loadImage("Images/Gui/Window/lb.png",true);
    applySurface(0,0, tmp_bg, background, nullptr);
    //nedre ramen
    tmp_bg = loadImage("Images/Gui/Window/bb.png",true);
    applySurface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
    //högra ramen
    tmp_bg = loadImage("Images/Gui/Window/rb.png",true);
    applySurface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
    //övre vänstra hörnet
    tmp_bg = loadImage("Images/Gui/Window/ltc.png",true);
    applySurface(0,0, tmp_bg, background, nullptr);
    //övre högra hörnet
    tmp_bg = loadImage("Images/Gui/Window/rtc.png",true);
    applySurface(w - tmp_bg->w,0, tmp_bg, background, nullptr);
    //nedre vänstra hörnet
    tmp_bg = loadImage("Images/Gui/Window/lbc.png",true);
    applySurface(0,h - tmp_bg->h, tmp_bg, background, nullptr);
    //nedre högra hörnet
    tmp_bg = loadImage("Images/Gui/Window/rbc.png",true);
    applySurface(w - tmp_bg->w, h - tmp_bg->h, tmp_bg, background, nullptr);
    
    //öppnar fonten	
    font_size = size;
    font_name = style;
    font = TTF_OpenFont(font_name.c_str(), font_size); 
    textColor = {255,255,255,0};
    font_bold = false;
    font_style = 0;
    font_italic = 0;
    font_underlined = 0;
    font_strikethrough = 0;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    clip.x = 0;
    clip.y = 0;
    clip.w = w;
    clip.h = h;
    
    textArea = SDL_CreateRGBSurface(0,clip.w,clip.h,32,0,0,0,1);	//skapar en ny tom yta
    applySurface(0,0, background, textArea, &clip);	
  }
		
  void Textbox::paint(Surface& to_where)
  {
    applySurface(box.x, box.y, textArea, to_where, &clip);
  }
    
  void Textbox::setColor(std::string& color)
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
  
  void Textbox::applyText(const std::string& what_text)
  {
    Surface tmp_surface;
    std::string tmp_word;
    tmp_surface = TTF_RenderText_Blended(font,what_text.c_str(),textColor);	//skapa en yta med ordet
    
    if(text_x + tmp_surface->w >= box.w - frame_size)								//om ordet inte får plats på den nuvarande raden		
      {
	text_x = frame_size;														//positionera x till början på raden
	text_y += 24;															//positionera y till nästa rad
      }
    
    applySurface(text_x,text_y, tmp_surface, textArea, nullptr);					//skriv ut den på ytan    
    text_x += tmp_surface->w-4;													//ompositionera var nästa ord ska starta				
  }

  void Textbox::setText(const std::string& what_text)
  {
    //Skapar yta att skriva på
    textArea = SDL_CreateRGBSurface(0,clip.w,clip.h,32,0,0,0,1);	//skapar en ny tom yta
    applySurface(0,0, background, textArea, &clip);				//ritar ut bakgrunden (ramen)
    
    std::queue<std::string> string_queue;
    text_x=frame_size;					//positionera ut startposition x-led
    text_y=frame_size;					//positionera ut startposition y-led
    font_style = 0;
    font_bold = false;
    font_italic = false;
    font_underlined = false;
    font_strikethrough = false;
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
	    text_x += tmp_word.size()*5;
	  }
	if(tmp_word.substr(0,1) != "<")
	  {
	    applyText(tmp_word);
	  }
	else if((tmp_word == "<n>" || tmp_word == "<\n>" || tmp_word == "<newline>"))
	  {
	    text_x = frame_size;														//positionera x till början på raden
	    text_y += 24;			
	  }
	else if((tmp_word == "<b>" || tmp_word == "<bold>") && !font_bold)
	  {
	    font_bold = true;
	    font_style += TTF_STYLE_BOLD;
	    TTF_SetFontStyle(font, font_style);				
	  }
	else if((tmp_word == "</b>" || tmp_word == "</bold>") && font_bold)
	  {
	    font_bold = false;
	    font_style -= TTF_STYLE_BOLD;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "<i>" || tmp_word == "<italic>") && !font_italic)
	  {
	    font_italic = true;
	    font_style += TTF_STYLE_ITALIC;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "</i>" || tmp_word == "</italic>") && font_italic)
	  {
	    font_italic = false;
	    font_style -= TTF_STYLE_ITALIC;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "<u>" || tmp_word == "<underlined>") && !font_underlined)
	  {
	    font_underlined = true;
	    font_style += TTF_STYLE_UNDERLINE;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "</u>" || tmp_word == "</underlined>") && font_underlined)
	  {
	    font_underlined = false;
	    font_style -= TTF_STYLE_UNDERLINE;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "<s>" || tmp_word == "<strikethrough>") && !font_strikethrough)
	  {
	    font_strikethrough = true;
	    font_style += TTF_STYLE_STRIKETHROUGH;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if((tmp_word == "</s>" || tmp_word == "</strikethrough>") && font_strikethrough)
	  {
	    font_strikethrough = false;
	    font_style -= TTF_STYLE_STRIKETHROUGH;
	    TTF_SetFontStyle(font,font_style);
	  }
	else if(tmp_word.find("<c|",0,3) != std::string::npos)
	  {
	    setColor(tmp_word);
	  }
	else if(tmp_word == "</c>")
	  {
	    tmp_word = "<c|ffffff>";
	    setColor(tmp_word);
	  }
      }
  }	
}//namespace
