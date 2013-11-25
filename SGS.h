#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "music.h"
#include "functions.h"
#include "Button.h"
#include "Slider.h"
#include "Textbox.h"
#include "Window.h"
#include "Checkbox.h"

#include <vector>

class SGS
{
protected:
//basvariabler som behövs för att SGS ska fungera
	SDL_Surface* background;
	SDL_Event event;
	SDL_Surface* screen;
	//object::pointer_arrow arrow;
	std::vector<Object::Object*> all_objects;
	
	virtual bool exit() = 0;
//variabler som finns för alla commands och liknande
	Music m;
	bool running = true;
	bool has_window = false;
	bool fullscreen = false;
	std::vector<std::pair<std::string, std::string>> settings;
	
public:
	//konstruktorer, destruktorer och operatorer
	SGS(SDL_Surface* scr) : screen(scr){
	   m.loadMusic("Music/Menu.wav");
	  loadSettings(settings);
	}
	~SGS();
	//borttagna
	SGS() = delete;                 //defaultkonstruktor
	SGS(const SGS&) = delete; //kopieringskonstruktor
	SGS(SGS&&) = delete;      //movekonstruktor
	SGS& operator=(const SGS&) = delete;
	SGS& operator=(SGS&&) = delete;
	
	//funktion för att köra programmet.
	virtual void run() = 0;
	
	//funktion med alla kommandon som finns
	virtual void run_command(const std::string& what_command) = 0; //finns skapad i "game_state_commands.cpp"
	
	//publika funktioner för att ladda background och skapa objekt i gamestatet
	void load_background(const std::string& bg){background = loadImage(bg);}
	bool make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command,
					 const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
	bool make_slider(const int& x_pos, const int& y_pos, const std::string& command);
	bool add_window(Object::Window* your_window);
	bool make_checkbox(int x, int y, const std:: string& command, bool checked = false);
	bool make_textbox(const std::string& text, const int& x, const int& y, const int& w, const int& h,
					  const SDL_Color &col = {255,255,255,0}, const std::string& font = "Fonts/LHANDW.TTF", const unsigned& size = 13);
};


class Menu : public SGS
{
private:
	void run_command(const std::string& what_command);
	void paint();
	bool exit();
	int networkThread(void* data); 
		
public:
	void run();
	~Menu();
	Menu(SDL_Surface* scr) : SGS(scr){
	  // m.loadMusic("Music/Menu.wav");
	  //loadSettings(settings);
	}
};
/*
class Game : public SGS
{
private:
	CardList card_deck;
	CardList discard_pile;
	vector<Player> players;
	Timer timer;
	map<std::string,SDL_Surface*> card_images;
	
	void paint();
	void setup();
	void game();
	void end();
	void run_command(const std::string& what_command);
public:
	~Game();
	
	Game(SDL_Surface* scr, Settings& set,vector<Player>& players) : SGS(scr)
	{
	  m.loadMusic("Music/Menu.wav");
	  load_settings(settings);
	}
	void run();
	
};
*/
#endif
