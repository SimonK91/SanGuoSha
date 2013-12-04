#ifndef PLAYER_H
#define PLAYER_H

#include "HeroCard.h"
#include "GameCard.h"
#include <stack>
#include <vector>
#include "PopupText.h"

struct Equipment
{
	Object::GameCard* def_horse = nullptr;
	Object::GameCard* off_horse = nullptr;
	Object::GameCard* weapon = nullptr;
	Object::GameCard* shield = nullptr;
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

  //--life
  Surface life_symbol;
  Surface life_symbol_empty;
  //--selected frame
  bool sel;
  Surface selected_frame;

 public:
  Player();
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
  void setStatus(unsigned);
  void setCurrentPlayer(bool cp){ current_player = cp; }
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
  unsigned getCurrentHP(){ return current_life; }
  
  void setRole(int r){role = r;}
  int getRole(){return role;}

  void fixCardPosition();
  void setSelected(bool);

};
#endif
