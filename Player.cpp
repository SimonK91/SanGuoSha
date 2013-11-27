#include "Player.h"


using namespace Object;

Player::Player() : role(-1),current_life(0),max_life(0), hero(nullptr)
{
  current_player = false;
}

Player::~Player()
{
	while(hand.size() != 0)
	{
		delete hand.front();
		hand.erase(hand.begin());
	}
	while(judgement_cards.size() != 0)
	{
		delete judgement_cards.top();
		judgement_cards.pop();
	}
	delete hero;
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
  std::cout << what_effect << std::endl;

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

void Player::paint(Surface screen)
{
  //rita ut handen l�ngst ner p� sk�rmen
  if(current_player == true)
    {
		for(auto i : hand)
		{
			i->paint(screen);
		}
		hero ->paint(screen);
    }
  
  //rita ut equipment
}

void Player::paint(Surface screen, int x_pos, int y_pos)
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
	  x_pos += 150;
    }
  hero->setPosition(805, 555);
}

std::string Player::handleEvent(const SDL_Event& event)
{
	std::string command;
	std::string tmpCommand;
	for(unsigned i = 0; i < hand.size(); ++i)
	{
		tmpCommand = hand.at(i) -> handleEvent(event);
		if(tmpCommand != "")
			command = tmpCommand;
	}
	return command;
}





