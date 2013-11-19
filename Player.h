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

  Equipment eq;

  int game_status;

  int player_nr;
  
  std::vector<Object::GameCard*> hand;

  Object::HeroCard* hero;

  std::stack<Object::GameCard> judgement_cards;


 public:
  Player();
  ~Player();

  void setHero(Object::HeroCard*);
  Object::GameCard* playCard(int);
  Object::GameCard* loseCard(int);
  void recieveCard(Object::GameCard*);
  Object::GameCard* loseEquipment(int);

  void doEffect(std::string);

  void setStatus(unsigned);
  bool entered();
  bool loading();
  bool left();

  void setPlayerNr(int);
  
  void paint(SDL_Surface*, bool);
  void paint(SDL_Surface*, int, int);
  
  void getHand();
  
  void setRole(int r){role = r;}
  int getRole(){return role;}

  void fixCardPosition();

};
#endif