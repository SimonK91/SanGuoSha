#include "functions.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <utility>
using namespace std;
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
	
	return optimizedImage;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface* Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT, const int& SCREEN_BPP)
{
	SDL_Surface* screen;

	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return nullptr;
	}
	
	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	//If there was an error in setting up the screen
	if (screen == nullptr)
	{
		return nullptr;
	}
	
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		return nullptr;
	}
	 
	//Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }
	//Set the window caption
	SDL_WM_SetCaption( "SanGuoSha", nullptr);
	
	//If everything is ok
	return screen;
}

void cleanUp(std::vector<SDL_Surface*> clean_surface, std::vector<TTF_Font*> clean_font)
{
	for(auto it = clean_surface.begin(); it != clean_surface.end(); ++it)
		SDL_FreeSurface(*it);
		
	for(int i = 0 ; i < clean_font.size(); ++i)
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
      return false;
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
  
  return true;
}

bool writeSettings(std::vector< std::pair<std::string, std::string>> settings)
{
  fstream write_to;
  write_to.open("Data/settings.txt");
  if(!write_to.is_open())
    {
      //filen kunde inte �ppnas
      return false;
    }
  write_to.clear();
  for(auto i : settings)
    {
      write_to << i.first << " " << i.second << std::endl;
    }
  write_to.close();
  
  return true;
}
