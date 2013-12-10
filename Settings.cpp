#include "Settings.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

Settings::Settings(const string& s)
{
  resolution.first = 800;
  resolution.first = 600;
  

  ifstream fs;
  fs.open(s);
  
  if(!fs.is_open())
    {
      throw runtime_error("GICK EJ ATT ÖPPNA DIN MAMMAS FIL");
    }
  
  string tmp;
  int i = 0;
  fs >> tmp; //ta bort FullScreen:
  fs >> tmp;
  
  if(tmp == "1")
    fullscreen == true;
  else
    fullscreen == false;
  
  fs >> tmp; //ta bort Music_Vol:
  fs >> i;
 
  if(i > 100)
    music_volume = 100;
  else if(i < 0)
    music_volume = 0;
  else
    music_volume = i;

  fs >> tmp; 
  fs >> i;
  
  if(i > 100)
   effect_volume = 100;
  else if(i < 0)
    effect_volume = 0;
  else
    effect_volume = i;

  std::string tmp_bool;
  fs >> tmp;
  fs >> tmp_bool;


  std::cerr << "Detta värde ges tool_tip: " << tmp_bool << std::endl; 
  if(tmp_bool == "0")
    {
      tool_tips = false;
    }
  else
    {
      tool_tips = true;
    }
  fs >> tmp;
  fs >> i;
  if(i >=5)
    {
      timer_time = i;
    }
  else
    {
      timer_time = 5;
    }
  fs.close();
}

void Settings::writeSettings(const string& s)
{ 
  ofstream fs;
  fs.open(s);
  fs << "Fullscreen: " << fullscreen << endl
     << "Music_Vol: " << music_volume << endl
     << "Effect_vol: " << effect_volume << endl
     << "Tool_tips: " << tool_tips << endl
     << "Timer_time: " << timer_time;
  fs.close(); 
}

void Settings::setMusicVolume(int vol)
{
  music_volume = vol;
}

void Settings::setEffectVolume(int vol)
{
  effect_volume = vol;
}
void Settings::setToolTips(bool tip)
{
  tool_tips = tip;
}









