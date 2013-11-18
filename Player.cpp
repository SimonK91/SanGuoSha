#include "Player.h"


using namespace Object;

Player::Player()
{
  
}

Player::~Player()
{
}

void Player::setHero(HeroCard* character)
{
  max_life = character->getHP();
  current_life = character->getHP();
  male = character->getMale();
  hero = character;
}

GameCard* Player::playCard(int index)
{
  GameCard* played_card = hand.at(index);
  std::vector<GameCard*>::iterator it = hand.begin() + index;
  hand.erase(it);
  
  fixCardPosition();
  return played_card;
}

GameCard* Player::loseCard(int index)
{
  GameCard* lost_card = hand.at(index);
  std::vector<GameCard*>::iterator it = hand.begin() + index;
  hand.erase(it);

  fixCardPosition();
  return lost_card;
}

void Player::recieveCard(GameCard* new_card)
{
  hand.push_back(new_card);
  fixCardPosition();
}

GameCard* Player::loseEquipment(int index)
{
  GameCard* lost_equipment = eq.equipment.at(index);
  
  std::vector<GameCard*>::iterator it = eq.equipment.begin() + index;
  eq.equipment.erase(it);

  return lost_equipment;
  
}

void Player::doEffect(std::string what_effect)
{
  //implementera senare

}

void Player::setStatus(unsigned status)
{
  game_status = status;
}

bool Player::entered()
{
  return game_status == 1;
}

bool Player::loading()
{
  return game_status == 0;
}

bool Player::left()
{
  return game_status == 2;
}

void Player::setPlayerNr(int nr)
{
  player_nr = nr;
}

void Player::paint(SDL_Surface* screen, bool current_player)
{
  //rita ut handen längst ner på skärmen
  if(current_player == true)
    {
      for(auto i : hand)
	{
	  i->paint(screen);
	}
    }
  
  hero->paint(screen);

  //rita ut equipment
}

void Player::paint(SDL_Surface* screen, int x_pos, int y_pos)
{
  
  hero->setPosition(x_pos, y_pos);
  hero->paint(screen);

  //rita ut equipment

}

void Player::fixCardPosition()
{
  int x_pos = 50;
  int y_pos = 500;
  
  for(auto i : hand)
    {
      i->setPosition(x_pos, y_pos);
    }
  hero->setPosition(550, 475);
}
