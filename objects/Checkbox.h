#ifndef checkbox_h
#define checkbox_h

#include "Objects.h"
#include <string>

namespace Object
{
  
  class Checkbox : public ActiveObject
  {
  private:
    bool checked = false;
    Surface box_sheet;
    std::vector<SDL_Rect> clip;
    std::string command;
    
  public:
    Checkbox(int x, int y, const std::string& command, bool check = false);    
    ~Checkbox() = default;
    
    void paint(Surface& to_where);    
    std::string handleEvent(const SDL_Event& event);
    void setChecked(bool check){checked = check;}
  };
  
} //namespace
#endif
