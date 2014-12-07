#ifndef SETTINGS_H
#define SETTINGS_H

#include <utility>
#include <string>

class Settings
{
 public:
  Settings(const std::string& s = "Data/settings.txt");
  ~Settings() = default;
  
  bool getFullscreen(){return fullscreen;}
  void setFullscreen(bool full){fullscreen = full;}
  int getMusicVolume(){return music_volume;}
  void setMusicVolume(int vol);
  void setEffectVolume(int vol);
  int getEffectVolume(){ return effect_volume;}
  std::pair<int,int> get_resolution(){return resolution;}
  void setToolTips(bool);
  bool getToolTips(){return tool_tips;}
  int getTimerTime(){return timer_time;}
  void setTimerTime(int time){timer_time = time;}
  
  void writeSettings(const std::string& s = "Data/settings.txt");
  
 private:
  int timer_time;
  bool fullscreen;
  int music_volume;
  int effect_volume;
  bool tool_tips;
  std::pair<int,int> resolution;
  
};
#endif
