#include "settings.h"

#include <fstream>
#include <stdexcept>
using namespace std;

Settings::Settings(const string& s){

//cout << "Holla holla, get " << s;

resolution.first = 800;
resolution.first = 600;

ifstream fs;
fs.open(s);

if(!fs.is_open())
	{throw runtime_error("GICK EJ ATT ÖPPNA DIN MAMMAS FIL");}

string tmp;
int i = 0;
fs >> tmp;

if(tmp == "1")
	fullscreen = true;
else
	fullscreen = false;

fs >> i;


if(i > 100)
	volume = 100;
else if(i < 0)
	volume = 0;
else
	volume = i;
 std::string tmp2;
 fs >> tmp2;
 name = tmp2;
fs.close();

	
}//Settings::Settings(string s)

void Settings::writeSettings(const string& s){

ofstream fs;
fs.open(s);
fs << fullscreen << " " << volume;
fs.close();

}//Settings::writeSettings











