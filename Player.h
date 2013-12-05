#ifndef PLAYER_H
#define PLAYER_H

#include "HeroCard.h"
#include "GameCard.h"
#include <stack>
#include <vector>
#include "PopupText.h"

struct Equipment
{
 
  SDL_Color pop_color = {255,255,255};
  
  Object::GameCard* def_horse = nullptr;
  Surface def_horse_image;
  Object::PopupText* def_horse_pop;

  Object::GameCard* off_horse = nullptr;
  Surface off_horse_image;
  Object::PopupText* off_horse_pop;

  Object::GameCard* weapon = nullptr;
  Surface weapon_image;
  Object::PopupText* weapon_pop;

  Object::GameCard* shield = nullptr;
  Surface shield_image;
  Object::PopupText* shield_pop;
 Equipment()
  {
    def_horse_pop = new Object::PopupText(0, 0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    off_horse_pop = new Object::PopupText(0, 0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    weapon_pop = new Object::PopupText(0,0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
    shield_pop = new Object::PopupText(0,0, 144,34, pop_color , "Fonts/LHANDW.TTF", 20);
  }
  ~Equipment()
  {
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
  Surface name;
  Surface hero_frame;
  Surface hero_profile;
  int role;
  int current_life;
  int max_life;
  bool male;
  bool current_player;
  int game_status;
  int player_nr;
  std::vector<Object::GameCard*> hand;
  Object::HeroCard* hero;
  std::stack<Object::GameCard*> judgement_cards;
  
  int player_x;
  int player_y;

  //--life
  Surface life_symbol;
  Surface life_symbol_empty;
  //--selected frame
  bool sel;
  Surface selected_frame;

 public:
  Player(const std::string&);
  ~Player();
  Equipment equipment;
  

  void setHero(Object::HeroCard*);
  Object::GameCard* playCard(int);
  Object::GameCard* loseCard(int);
  void recieveCard(Object::GameCard*);
  Object::GameCard* loseEquipment(int);
  bool hasHero(){return hero != nullptr;}

  void doEffect(std::string);

  void modifyLife(int mod)
  { 
	if(current_life + mod <= max_life)
		current_life += mod; 
  }
  void addJudgementCard(Object::GameCard* gc)
  {
	judgement_cards.push(gc);
  }
  Object::GameCard* getJudgementCard()
  {
	Object::GameCard* gc = judgement_cards.top();
	judgement_cards.pop();
	return gc;
  }
  int getLife(){ return current_life; }
  int getMaxLife(){ return max_life; }
  void setStatus(unsigned);
  void setCurrentPlayer(bool cp);
  bool isCurrentPlayer(){ return current_player; }
  bool entered();
  bool loading();
  bool left();

  Object::GameCard* handleHand(const SDL_Event& event);
  bool handleEvent(const SDL_Event& event);
  void setPlayerNr(int);
  void paint(Surface);
  void paint(Surface, int, int);
  
  const std::vector<Object::GameCard*>& getHand(){ return hand; } //only read not whrite
  unsigned getHandSize(){ return hand.size(); }
  //unsigned getCurrentHP(){ return current_life; }
  
  void setRole(int r){role = r;}
  int getRole(){return role;}
  std::string getHeroName(){return hero->getName();}

  void fixCardPosition();
  void setSelected(bool);
  Object::GameCard* equipStuff(Object::GameCard* gear);

  void setPos(int x_pos, int y_pos);

};
#endif
