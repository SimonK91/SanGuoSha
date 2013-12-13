#ifndef PLAYER_H
#define PLAYER_H

#include "HeroCard.h"
#include "GameCard.h"
#include <stack>
#include <vector>
#include "PopupText.h"
#include "Clickbox.h"

struct Equipment
{
  SDL_Color pop_color;
  
  Object::GameCard* def_horse = nullptr;
  Surface def_horse_image;
  Surface def_horse_image_thin;
  Object::PopupText* def_horse_pop;
  
  Object::GameCard* off_horse = nullptr;
  Surface off_horse_image;
  Surface off_horse_image_thin;
  Object::PopupText* off_horse_pop;
  
  Surface weapon_selected_frame;
  Object::Clickbox* weapon_click;
  Object::GameCard* weapon = nullptr;
  Surface weapon_image;
  Surface weapon_image_thin;
  Object::PopupText* weapon_pop;
  
  Object::GameCard* shield = nullptr;
  Surface shield_image;
  Surface shield_image_thin;
  Object::PopupText* shield_pop;
  
  Equipment()
  {
	 pop_color.r = 255;
    pop_color.g = 130;
    pop_color.b = 255;
    def_horse_pop = new Object::PopupText(0, 0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    off_horse_pop = new Object::PopupText(0, 0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    weapon_pop = new Object::PopupText(0,0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    shield_pop = new Object::PopupText(0,0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
	weapon_click = new Object::Clickbox(5,550,144,34, "activate");
	weapon_selected_frame = loadImage("Images/Gui/activated_weapon_frame.png", true);
  }
  ~Equipment()
  {
  	delete def_horse_pop;
	delete off_horse_pop;
	delete weapon_pop;
	delete shield_pop;
	
    if(weapon != nullptr)
      delete weapon;
    if(shield != nullptr)
      delete shield;
    if(off_horse != nullptr)
      delete off_horse;
    if(def_horse != nullptr)
      delete def_horse;
  }
};

class Player
{
 private:
	std::string player_name;
	Surface acedia;
	Surface lightning;
  Surface name;
  Surface hero_frame;
  Surface hero_profile;
  Surface player_role;
  int role;
  int current_life;
  int max_life;
  bool male;
  bool current_player;
  int game_status;
  int player_nr;
  bool alive;
  std::vector<Object::GameCard*> hand;
  Object::HeroCard* hero;
  std::vector<Object::GameCard*> judgement_cards;

  int player_x;
  int player_y;
  
  Surface life_symbol;
  Surface life_symbol_empty;

  bool sel;
  Surface selected_frame;
	bool weapon_activated;

 public:
  Player(const std::string&);
  ~Player();

  Equipment equipment;
  
bool getWeaponActivated(){return weapon_activated;}
  void setHero(Object::HeroCard*);
  Object::GameCard* playCard(int);
  Object::GameCard* loseCard(int);
  void recieveCard(Object::GameCard*);
  Object::GameCard* loseEquipment(int);
  bool hasHero(){return hero != nullptr;}
  bool hasEquipment(){ return (equipment.weapon != nullptr)||(equipment.shield != nullptr)||(equipment.def_horse != nullptr)||(equipment.off_horse != nullptr);}

  void doEffect(std::string);
  void modifyLife(int mod)
  { 
    if(current_life + mod <= max_life)
      current_life += mod;
  }
  void addJudgementCard(Object::GameCard* gc)
  {
    judgement_cards.push_back(gc);
  }
  Object::GameCard* getJudgementCard()
  {
	  if(!judgement_cards.empty())
	  {
		  Object::GameCard* gc = judgement_cards.back();
		  judgement_cards.pop_back();
		  return gc;
	  }
	  return nullptr;
  }
  
  bool hasAcedia();
  bool hasLightning();
  int getLife(){ return current_life; }
  int getMaxLife(){ return max_life; }
  void setStatus(unsigned);
  void setCurrentPlayer(bool cp){ current_player = cp; }
  bool isCurrentPlayer(){ return current_player; }
  bool entered();
  bool loading();
  bool left();
  void kill(){alive = false;}
  bool isAlive(){return alive;}
  Object::GameCard* activatedWeapon();
  Object::GameCard* handleHand(const SDL_Event& event);
  bool handleEvent(const SDL_Event& event);
  void setPlayerNr(int);
  void paint(Surface);
  void paint(Surface, int, int);
  
  const std::vector<Object::GameCard*>& getHand(){ return hand; } //only read not whrite
  unsigned getHandSize(){ return hand.size(); }
  
  void setRole(int r);
  int getRole(){return role;}
  std::string getHeroName(){return hero->getName();}
  
  void fixCardPosition();
  void setSelected(bool);
  bool getSelected()const{return sel;}
	  std::string getName(){return player_name;}
  void setPos(int x_pos, int y_pos);
  Object::GameCard* equipStuff(Object::GameCard* gear, int type);
  void showToolTip(Surface);
  void handleToolTip(SDL_Event&);
};
#endif
