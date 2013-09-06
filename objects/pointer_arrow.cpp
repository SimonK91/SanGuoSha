#include "pointer_arrow.h"

namespace object
{

void pointer_arrow::update_coordinates(const SDL_Event& event)
{
	x = event.motion.x;
	y = event.motion.y;
}

}//slut på namnrymden