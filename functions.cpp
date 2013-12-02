#include "functions.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <utility>
using namespace std;

void Surface::setImage(Surface tmp)
{
	if(tmp.getImage() == nullptr)
		return;
	if(image != nullptr)
		SDL_FreeSurface( image );
	image = tmp.getImage();

}
void Surface::setImage(SDL_Surface* tmp)
{
	if(tmp == nullptr)
		return;
	if(image != nullptr)
		SDL_FreeSurface( image );
	image = tmp;
}
Surface& Surface::operator=(SDL_Surface* other)
{
	if(other)
	{
		if(image != nullptr)
			SDL_FreeSurface(image);
		image = other;
	}
	else
		throw SGS_error("Could not set surface: " + name);
		
	return *this;
}

SDL_Surface* loadImage(const string& filename,bool transparant, const Uint8& red, const Uint8& green, const Uint8& blue, bool color_key)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = nullptr;
	
	//The optimized image that will be used
	SDL_Surface* optimizedImage = nullptr;
	
	// laddar in bilden till temporÃ¤ra
	loadedImage = IMG_Load( filename.c_str() );
	if(loadedImage != nullptr)
	{
		if(transparant)
			optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
		else
		{
			//create an optimized image
			optimizedImage = SDL_DisplayFormat( loadedImage );
				
			//set color key if added colors
			if(color_key)
			{
				Uint32 colorkey = SDL_MapRGB( optimizedImage->format, red, green, blue );
				SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
			}
		}
		//free the old image
		SDL_FreeSurface( loadedImage );
	}
	else
	{
		throw SGS_error("could not open file: "+filename+'.');
	}
	return optimizedImage;
}

void applySurface(int x, int y, Surface& source, Surface& destination, SDL_Rect* clip)
{
// int counter = 0;
// std::cout << "apply surface: " << ++counter << std::endl;
	if(source.getImage() == nullptr)
	{
		// std::cout << "apply surface in if: " << counter << std::endl;
		throw SGS_error("applySurface failed - nullpointer exception, source: "+source.getName());
		// std::cout << "apply surface in if: " << counter << std::endl;
	}
	// std::cout << "apply surface: " << ++counter << std::endl;
	SDL_Rect offset;
	// std::cout << "apply surface: " << ++counter << std::endl;
	offset.x = x;
	offset.y = y;
	// std::cout << "apply surface: " << ++counter << std::endl;
	SDL_BlitSurface( source.getImage(), clip, destination.getImage(), &offset );
	// std::cout << "apply surface: " << ++counter << std::endl;
}

Surface Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT, const int& SCREEN_BPP)
{
	Surface* screen = new Surface("screen");

	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		throw SGS_error("Init - SDL_Init failed to open");
	}
	
	//Set up the screen
	*screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	//If there was an error in setting up the screen
	if (screen->getImage() == nullptr)
	{
		throw SGS_error("Init - Could not set up the screen");
	}
	
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		throw SGS_error("Init - TTF_Init failed to open");
	}
	 
	//Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        throw SGS_error("Init - Mix_OpenAudio failed to open");
    }
	//Set the window caption
	SDL_WM_SetCaption( "SanGuoSha", nullptr);
	
	//If everything is ok
	std::cout << "Initialize is okay!" << std::endl;
	return *screen;
}

void cleanUp(std::vector<TTF_Font*> clean_font)
{
	for(unsigned i = 0 ; i < clean_font.size(); ++i)
		TTF_CloseFont(clean_font.at(i));
}

//Integer to string
std::string I2S(const int& i)
{
	std::stringstream ss;
	ss << i;
	std::string s = ss.str();
	return s;
}

int S2I(const std::string& s)
{
	int value = 0;
	for(char c: s)
	{
		value = value*10 + (c - '0');
	}
	return value;
}

	 
bool loadSettings(std::vector<std::pair<std::string, std::string>>& settings)
{
  std::ifstream read_from("Data/settings.txt");
  
  if(!read_from.is_open())
    {
      //filen kunde inte �ppnas
      throw SGS_error("Settings - Could not open \"Data/settings.txt\"");
    }
  
  std::string tmpSetting = "";
  std::string tmpValue = "";
  
  while(read_from >> tmpSetting)
    {
      read_from >> ws;
      read_from >> tmpValue;
      settings.push_back(std::make_pair(tmpSetting, tmpValue) );
    }
  
  read_from.close();
  std::cout << "Load settings okay!" << std::endl;
  return true;
}

bool writeSettings(std::vector< std::pair<std::string, std::string>> settings)
{
  fstream write_to;
  write_to.open("Data/settings.txt");
  if(!write_to.is_open())
    {
      //filen kunde inte �ppnas
      throw SGS_error("Settings - Could not open \"Data/settings.txt\"");
    }
  write_to.clear();
  for(auto i : settings)
    {
      write_to << i.first << " " << i.second << std::endl;
    }
  write_to.close();
  std::cout << "Write settings okay!" << std::endl;
  return true;
}

