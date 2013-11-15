#include "Picture.h"

#include "../Functions.h"
namespace Object
{
  Picture::Picture(int x_pos, int y_pos, std::string image, SDL_Rect in_clip)
  {
    image = loadImage(image, true);
    pos.x = x_pos;
    pos.y = y_pos;
    clip = in_clip;
  }
  
  Picture::~Picture()
  {
  }
  void Picture::Paint(SDL_Surface* to_where)
  {
    applySurface(pos.x, pos.y, image, to_where, &clip);
  }
  
}//namespace
