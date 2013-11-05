#include <string>

#include "object_button.h"


namespace object
{
	class slider : public active_object
	{
		public:
		
		slider(const int& x, y, const std::string& bg_i = "Images/Gui/borderBottom.png", 
			const std::string& btn_i = "Images/Gui/borderLeftBottomCorner.png")
		{
		SDL_Surface* load_image(const string& filename,bool transparant, const Uint8& red, const Uint8& green, const Uint8& blue, bool color_key)

			bg = loadimage(bg_i, true);
			btn = loadimage(btn_i, true) ;		
		}
		
		
		
		protected:	
			//Nej
		
		private:
		object::button this_button("",x,y,"",btn, 20, 20);
		SDL_Surface* bg;
		SDL_Surface* btn;
		
	}
}

//Hej