#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "FrameRateFixer.h"
#include "music.h"
#include "functions.h"
#include "Button.h"
#include "Slider.h"
#include "Textbox.h"
#include "Window.h"
#include "Checkbox.h"
#include "CardList.h"

#include "Player.h"

#include <vector>

class SGS
{
protected:
//basvariabler som behövs för att SGS ska fungera
	Surface background;
	SDL_Event event;
	Surface screen;
	//object::pointer_arrow arrow;
	std::vector<Object::Object*> all_objects;
	
	virtual bool exit() = 0;
//variabler som finns för alla commands och liknande
	Music m;
	FrameRateFixer fps;
	bool running = true;
	bool has_window = false;
	bool fullscreen = false;
	std::vector<std::pair<std::string, std::string>> settings;
	
public:
	//konstruktorer, destruktorer och operatorer
	SGS(Surface scr) : screen(scr),m("Music/Menu.wav"), fps(30){}
	~SGS();
	//borttagna
	SGS() = delete;           //defaultkonstruktor
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
	bool make_textbox(const int& x, const int& y, const int& w, const int& h,
					  const unsigned& size = 13, const std::string& font = "Fonts/LHANDW.TTF");
					  void set_text(const int& where, const std::string& what_text);
};


class Menu : public SGS
{
private:
	void run_command(const std::string& what_command);
	void paint();
	bool exit();
		
public:
	void run();
	~Menu() = default;
	Menu(Surface scr) : SGS(scr){
	  m.loadMusic("Music/Menu.wav");
	}
};

class Game : public SGS
{
private:
	unsigned self;
	unsigned state;
	bool run_next;
	
	int game_stage;
	
	Object::Button* play_card = new Object::Button("play card", 800, 630, "play_card", "Images/Gui/smallButton.png", 20);
	Object::Button* end_turn = new Object::Button("end turn", 800, 575, "end_turn", "Images/Gui/smallButton.png", 20);
	
	Player* target_player;
	Player* current_player;
	Object::GameCard* selected_card;
	
	Object::CardList* card_deck;
	Object::CardList* discard_pile;
	Object::CardList* hero_deck;
	std::vector<Player*> players;
	//Timer timer;
	//map<std::string,SDL_Surface*> card_images;
	
	void paint();
	void run_command(const std::string& what_command);
	Object::GameCard* run_effect(Object::GameCard* gc);
	bool loadup(){return true;} //dne är skriven här
	void UI();
public:
	~Game() = default;
	Game() = default;
	
	Game(Surface scr) : SGS(scr), game_stage(0), target_player(nullptr), current_player(nullptr), selected_card(nullptr)
	{
		self = 0; //ska komma utifrån!!
		card_deck = new Object::CardList("standard_playing_cards");
		discard_pile = new Object::CardList("empty");
		hero_deck = new Object::CardList("hero_deck");
		m.loadMusic("Music/Menu.wav");
		Player* p1;
		for(unsigned i = 0 ; i < 1 ; ++i)
		{
			p1 = new Player();
			p1->setStatus(1);
			players.push_back(p1);
		}
		state = 1;
	}
	
	bool runNext(){return run_next;}
	void run();
	void setup();
	void end();
	bool exit();
	
};

#endif
