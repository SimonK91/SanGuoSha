#include <string>

#include "objects.h"


namespace object
{
	class slider : public active_object
	{
		public:
		
		slider(const int& x, y, const std::string& bg_i = "Images/Gui/borderBottom.png", 
			const std::string& btn_i = "Images/Gui/borderLeftBottomCorner.png")
		{
		
			bg = loadimage(bg_i, true);
			btn = loadimage(btn_i, true) ;		
		}
		
		
		
		protected:	
			//Nej
		
		private:
		SDL_Surface* bg;
		SDL_Surface* btn;
		
	}
}

//Hej