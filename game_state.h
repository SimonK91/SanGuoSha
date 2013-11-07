#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "music.h"
#include "functions.h"
#include "pointer_arrow.h"
#include "object_button.h"
#include "object_slider.h"
#include "object_text_box.h"
#include "gameCard.h"
#include "object_window.h"

#include <vector>

class GameState
{
private:
//basvariabler som behövs för att gamestate ska fungera
	SDL_Surface* background;
	SDL_Event event;
	SDL_Surface* screen;
	object::pointer_arrow arrow;
	std::vector<object::object*> all_objects;
	
	Music m;

//variabler som finns för alla commands och liknande
	bool running = true;
	bool has_window = false;
	bool fullscreen = false;
	std::vector<std::pair<std::string, std::string>> settings;
	
public:
	//konstruktorer, destruktorer och operatorer
	GameState(SDL_Surface* scr) : screen(scr){
	  m.loadMusic("Music/Menu.wav");
	  load_settings(settings);
	}
	~GameState();
	//borttagna
	GameState() = delete;                 //defaultkonstruktor
	GameState(const GameState&) = delete; //kopieringskonstruktor
	GameState(GameState&&) = delete;      //movekonstruktor
	GameState& operator=(const GameState&) = delete;
	GameState& operator=(GameState&&) = delete;
	
	//funktion för att köra programmet.
	void run();
	
	//funktion med alla kommandon som finns
	void run_command(const std::string& what_command, unsigned& current_command); //finns skapad i "game_state_commands.cpp"
	
	//publika funktioner för att ladda background och skapa objekt i gamestatet
	void load_background(const std::string& bg){background = load_image(bg);}
	bool make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command,
					 const std::string& image = "Images/Gui/cleanButton2.png", const unsigned& size = 20);
	bool make_slider(const int& x_pos, const int& y_pos, const std::string& command);
	bool add_window(object::window* your_window);
	bool make_textbox(const std::string& text, const int& x, const int& y, const int& w, const int& h,
					  const SDL_Color &col = {255,255,255,0}, const std::string& font = "Fonts/LHANDW.TTF", const unsigned& size = 13);
};

#endif
