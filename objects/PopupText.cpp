#include "PopupText.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace Object
{
  PopupText::PopupText(int x_pos, int y_pos, int width, int height, SDL_Color color, std::string f, unsigned font_size)
  {
    text_x = x_pos;
    text_y = y_pos;
    text_color = color;
    font = TTF_OpenFont(f.c_str(), font_size);
    show_text = false;
    box.x = x_pos;
    box.y = y_pos;
    box.w = width;
    box.h = height;

    //backrundbild
    background = loadImage("Images/Gui/popupBackground.png", true);
  }
  
  
  PopupText::~PopupText()
  {
     cleanUp({font});
  }
  
  void PopupText::setColor(std::string color)
  {
    color.erase(0,3);			//tar bort de första tecknena ("<|c")		
    color.resize(color.size()-1);	//tar bort det sista tecknet (dvs '>')
    if(color.size() != 6)	       //kontrollerar så att det finns 6 tecken kvar (0-255 i hex)
      return;			      //om inte, gå ut
    
    std::stringstream ss(color);    //mata in strängen i stringstream
    std::vector<Uint8> tmp;	  //skapa en vektor för att lagra värdet på varje tecken
    
    for(Uint8 temp ; ss >> temp;)    //sparar värdet i ett temporärt ställe för att direkt pushas in i vektorn
      {
	tmp.push_back(temp);				   //pushas in
	if(tmp.back() >= '0' && tmp.back() <= '9')	  //om tecknet är mellan 0-9, ge värdet 0-9
	  tmp.back() = tmp.back() - '0';
	else if(tmp.back() >= 'a' && tmp.back() <= 'f')	 //om tecknet är mellan a-f, ge värdet 10-15
	  tmp.back() = tmp.back() - 'a' + 10;
	else if(tmp.back() >= 'A' && tmp.back() <= 'F')	//om tecknet är mellan A-F, ge värdet 10-15
	  tmp.back() = tmp.back() - 'A' + 10;
	else
	  return;				      // annars är tecknet ogiltligt och funktionen avbryts
      }

    Uint8 r = tmp[0]*16 + tmp[1];		     //lagra de två första bitarna i "röd färg",
    Uint8 g = tmp[2]*16 + tmp[3];		    //grön färg
    Uint8 b = tmp[4]*16 + tmp[5];		    //blå färg
    text_color = SDL_Color{r,g,b,0};		   //sätt "textColor" till de nya värdena 
  }
  
  std::string PopupText::handleEvent(const SDL_Event& event)
  {
    int x = 0;
    int y = 0;
    if(event.type == SDL_MOUSEMOTION)
      {
	x = event.motion.x;
	y = event.motion.y;
	text_x = x;
	text_y = y - 20;
	
	if(x > box.x && x < (box.x + box.w) && y > box.y && y < (box.y + box.h))
	  {
	    show_text = true;
	  }
	else
	  {
	    show_text = false;
	  }
      }
    return "";
  }
  
  void PopupText::paint(Surface& to_where)
  {
    if(text_area.getImage() != nullptr)
      {
	SDL_Rect text_rect;
	text_rect.x = 0;
	text_rect.y = 0;
	text_rect.w = text_area->w + 20;
	text_rect.h = text_area->h + 10;
	if(show_text == true)
	  {
	    applySurface(text_x - 10, text_y -5, background, to_where, &text_rect);
	    applySurface(text_x, text_y, text_area, to_where, NULL);
	  }

      }
  }
  
  void PopupText::setFileText(std::string file, std::string keyword)
  {
    std::ifstream read_file(file);
    std::string read_text = "";
    std::string tmp_text;
    if(read_file.is_open())
      {
	while(std::getline(read_file, tmp_text))
	  {
	    if(tmp_text == keyword)
	      {
		std::cerr << "fond keyword in file " << keyword  << std::endl;
		std::getline(read_file, read_text);
		read_file.close();
		break;
	      }
	  } 
      }
    else
      {
	std::cerr << "could not read text from file, keyword was " << keyword << std::endl;
	read_text = "error reading text from file!";
      }

    setText(read_text);

  }

  void PopupText::setPos(int x_pos, int y_pos)
  {
    box.x = x_pos;
    box.y = y_pos;
  }
  
  void PopupText:: setText(std::string text)
  {
    text_area.setImage(TTF_RenderText_Solid(font, text.c_str(), text_color));
     SDL_Rect text_rect;
    text_rect.x = 0;
    text_rect.y = 0;
    text_rect.w = text_area->w + 20;
    text_rect.h = text_area->h + 10;
    //ramen
	background = loadImage("Images/Gui/popupBackground.png", true);
    Surface tmp_border;
    tmp_border.setImage( loadImage("Images/Gui/Window/tb.png", true));
    applySurface(0,0, tmp_border, background, nullptr);
    frame_size = tmp_border.getImage()->h;
    tmp_border.setImage(loadImage("Images/Gui/Window/lb.png", true));
    applySurface(0,0, tmp_border, background, nullptr);
    tmp_border.setImage(loadImage("Images/Gui/Window/bb.png", true));
    applySurface(0,text_rect.h - tmp_border.getImage()->h, tmp_border, background, nullptr);

    tmp_border.setImage(loadImage("Images/Gui/Window/rb.png", true));
    applySurface(text_rect.w - tmp_border->w, 0, tmp_border, background, nullptr);

    tmp_border.setImage(loadImage("Images/Gui/Window/ltc.png", true));
    applySurface(0,0, tmp_border, background, nullptr);
        
    tmp_border.setImage( loadImage("Images/Gui/Window/rtc.png", true));
    applySurface(text_rect.w - tmp_border.getImage()->w,0, tmp_border, background, nullptr);
        
    tmp_border.setImage(loadImage("Images/Gui/Window/lbc.png", true));
    applySurface(0, text_rect.h - tmp_border.getImage()->h, tmp_border, background, nullptr);
     
    tmp_border.setImage(loadImage("Images/Gui/Window/rbc.png", true));
    applySurface(text_rect.w - tmp_border.getImage()->w, text_rect.h - tmp_border->h, tmp_border, background, nullptr);
  }
  
}//namespace
