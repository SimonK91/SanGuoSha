#ifndef PLAYER_H
#define PLAYER_H

#include "HeroCard.h"
#include "GameCard.h"
#include <stack>
#include <vector>
#include "PopupText.h"

struct Equipment
{
  std::vector<Object::GameCard*> equipment;
  
};

class Player
{
 private:
  int role;
  int current_life;
  int max_life;
  bool male;
  bool current_player;
  Equipment eq;
  int game_status;
  int player_nr;
  std::vector<Object::GameCard*> hand;
  Object::HeroCard* hero;
  std::stack<Object::GameCard*> judgement_cards;

 public:
  Player();
  ~Player();

  void setHero(Object::HeroCard*);
  Object::GameCard* playCard(int);
  Object::GameCard* loseCard(int);
  void recieveCard(Object::GameCard*);
  Object::GameCard* loseEquipment(int);
  bool hasHero(){return hero != nullptr;}

  void doEffect(std::string);

  void setStatus(unsigned);
  void setCurrentPlayer(bool cp){ current_player = cp; }
  bool isCurrentPlayer(){ return current_player; }
  bool entered();
  bool loading();
  bool left();

  std::string handleEvent(const SDL_Event& event);
  void setPlayerNr(int);
  void paint(Surface);
  void paint(Surface, int, int);
  
  const std::vector<Object::GameCard*>& getHand(){ return hand; } //only read not whrite
  unsigned getHandSize(){ return hand.size(); }
  unsigned getCurrentHP(){ return current_life; }
  
  void setRole(int r){role = r;}
  int getRole(){return role;}

  void fixCardPosition();

};
#endif
