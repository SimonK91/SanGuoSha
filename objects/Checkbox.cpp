#include "Checkbox.h"

namespace Object
{
  
  Checkbox::Checkbox(int x, int y, const std::string& com, bool check)
  {
    checked = check;
    command = com;

    box_sheet = loadImage("Images/Gui/checkBox.png", true); //fixa bilden
    box.x = x;
    box.y = y;
    box.h = box_sheet.getImage()->h / 2;
    std::cerr << "bildens bredd anges som: " << box_sheet.getImage()->w << std::endl;
    box.w = box_sheet.getImage()->w; 
  
    
    SDL_Rect temp_clip;
    temp_clip.x = 0;
    temp_clip.y = 0;
    temp_clip.h = box.h;
    temp_clip.w = box.w;
    
    clip.push_back(temp_clip);		
    temp_clip.y +=  box.h;
    clip.push_back(temp_clip);
  }
  
  void Checkbox::paint(Surface& to_where)
  {
    if(checked)
      applySurface(box.x, box.y, box_sheet, to_where, &clip.at(1));
    else
      applySurface(box.x, box.y, box_sheet, to_where, &clip.at(0));   
  }
  
  std::string Checkbox::handleEvent(const SDL_Event& event)
  {
    static bool changed = false;
    std::string bool_checker = "";
    if(event.type == SDL_MOUSEBUTTONDOWN)
      {      
	int pointer_x = event.motion.x;
	int pointer_y = event.motion.y;
	
	//kolla om vi är inom knappen med musen
	if(pointer_x > box.x && pointer_x < (box.x + box.w) && pointer_y > box.y && pointer_y < (box.y + box.h) && !changed)
	  {
	    checked = ! checked;
	    changed = ! changed;
	    if(checked == true)
	      {
		bool_checker = "true";
	      }
	    else
	      {
		bool_checker = "false";
	      }
	return command + bool_checker;
	  }
      }
    else if(event.type == SDL_MOUSEBUTTONUP)
      {
	changed = false;	//finns för att vi bara ska registrera en knapptryckning
      }
    return "";
  }  
} //nameapace
