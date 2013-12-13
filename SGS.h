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
#include "Timer.h"
#include "Player.h"
#include <vector>
#include "Settings.h"
#include "SDL/SDL_thread.h"

class SGS
{
protected:
  Surface background;
  SDL_Event event;
  Surface screen;
  std::vector<Object::Object*> all_objects;
  
  virtual bool exit() = 0;
  Music m;
  FrameRateFixer fps;
  bool running = true;
  bool has_window = false;
  bool fullscreen = false;
  std::vector<std::pair<std::string, std::string>> settings;
  Settings sett;
  
public:
  SGS(Surface scr) : screen(scr),m("Music/Menu.wav"), fps(30){

    m.loadMusic("Music/Menu.wav");
    m.loadSoundEffect("Music/shield-equip.wav");
    m.loadSoundEffect("Music/weapon-equip.wav");
    m.loadSoundEffect("Music/horse-equip.wav");
    m.loadSoundEffect("Music/dismantle.wav");
    m.loadSoundEffect("Music/steal.wav");
    m.loadSoundEffect("Music/barbarians.wav");
    m.loadSoundEffect("Music/arrows.wav");
    m.loadSoundEffect("Music/dodge.wav");
    m.loadSoundEffect("Music/draw2-cards.wav");
    m.loadSoundEffect("Music/hero-pick.wav");
  }
  ~SGS(); //ta bort ljud effecter
  
  //borttagna
  SGS() = delete;
  SGS(const SGS&) = delete;
  SGS(SGS&&) = delete;      
  SGS& operator=(const SGS&) = delete;
  SGS& operator=(SGS&&) = delete;
  
  virtual void run() = 0;
  virtual void run_command(const std::string& what_command) = 0; //finns skapad i "game_state_commands.cpp"

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
  Menu(Surface scr) : SGS(scr)
  {
  }
  ~Menu() = default;
  
  void run();
};

class Game : public SGS
{
private:
  unsigned self;
  int state;
  bool run_next;
  Uint8 *keystates;
  int game_stage;
  
  std::vector<Player*> target_player;
  Player* current_player;
  Player* source_player;
  Object::GameCard* selected_card;
  
  bool ruleTargetOK(Player*);
  bool rulePlayCardOK();
  
  int getDistance(Player* source, Player* target);
  Object::CardList* card_deck;
  Object::CardList* discard_pile;
  Object::CardList* hero_deck;
  std::vector<Player*> players;
  Timer* timer;
  
  bool negated(const std::string& description = "no description added - negate something");
  void harvest();
  bool acedia();
  bool lightningExplode();
  bool useCard(const std::string&, const std::string&, Player*);
  bool shieldBlock(std::string, int p_index = 0);
  
  void cleanPlayer(Player*);
  
  void exitCommand(SDL_Event&);
  
  void paint();
  void run_command(const std::string& what_command);
  Object::GameCard* run_effect(Object::GameCard* gc);
  bool loadup(){return true;}
  void UI();

 public:
  ~Game() = default;
  Game() = default;
 
 Game(Surface scr, Settings settings) : SGS(scr), game_stage(0), current_player(nullptr), selected_card(nullptr)
  {
    sett = settings;
    self = 0; //ska komma utifrån!!
    card_deck = new Object::CardList("standard_playing_cards");
    discard_pile = new Object::CardList("empty");
    hero_deck = new Object::CardList("hero_deck");
    m.loadMusic("Music/Menu.wav");
    Player* p1;
    for(unsigned i = 0 ; i < 5 ; ++i)
      {
	p1 = new Player("Player "+I2S(i));
	p1->setStatus(1);
	players.push_back(p1);
      }
    state = 1;
    timer = new Timer(5,500,5,"end_turn");
    keystates = SDL_GetKeyState(nullptr);
    
  }
  
  int nextPlayer(int unique = -1);
  bool runNext(){return run_next;}
  void run(){}
  void runHotseat();
  void setup();
  void setupHotseat();
  void end();
  bool exit();
	
};

#endif
