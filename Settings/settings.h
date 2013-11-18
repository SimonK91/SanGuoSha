#ifndef SETTINGS_H
#define SETTINGS_H

#include <utility>
#include <string>

class Settings{
public:
Settings(const std::string& s = "settings.txt");
~Settings() = default;

bool get_fullscreen(){return fullscreen;}
int get_volume(){return volume;}
std::pair<int,int> get_resolution(){return resolution;}

void writeSettings(const std::string& s = "settings.txt");

private:

bool fullscreen;
int volume;
std::pair<int,int> resolution;

};

#endif /*SETTINGS_H*/