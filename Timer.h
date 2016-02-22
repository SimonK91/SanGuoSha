#ifndef TIMER_H
#define TIMER_H
#include "Functions.h"

class Timer
{
private:
  Surface bar;
  Surface frame;
  int start_ticks;
  int paused_ticks;
  
  bool started;
  bool paused;
  SDL_Rect pos;
  int seconds;
  std::string command;
  
public:
  Timer(int x_pos, int y_pos, int sec, std::string com);
  ~Timer();
  
  void start(int sec);
  void stop();
  void pause();
  void unPause();
  
  int getTicks();
  
  bool checkStarted();
  bool checkPaused();
  
  void paint(Surface);
  void setPos(int x_pos, int y_pos);
  void setCommand(std::string);
  void reset(int time, std::string cmd);
  std::string getCommand(){return command;}
  std::string time_ran_out();
};
#endif
