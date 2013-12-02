#ifndef PICTURE_H
#define PICTURE_H
#include "Objects.h"

namespace Object
{
  class Picture : public DeadObject
  {
    
  private:
    Surface image;
    SDL_Rect pos;
  SDL_Rect clip;
  
  public:
  Picture(int pos_x, int pos_y, std::string image, SDL_Rect clip);
  ~Picture();
  
  void Paint(Surface& to_where);
  
  
  };
}//namespace
#endif
