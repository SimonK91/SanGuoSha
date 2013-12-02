#include "Player.h"


using namespace Object;

Player::Player() : role(-1),current_life(0),max_life(0), hero(nullptr)
{
  current_player = false;
  sel = false;
  selected_frame.setImage(loadImage("Images/Cards/Characters/hero-frame.png",true));
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

  if(hero->getClan() == red)
    { 
      life_symbol.setImage(loadImage("Images/Cards/Characters/life-red.png",true));
    }
  else if(hero->getClan() == green)
    {
      life_symbol.setImage(loadImage("Images/Cards/Characters/life-green.png",true));
    }
  else if(hero->getClan() == blue)
    {
      life_symbol.setImage(loadImage("Images/Cards/Characters/life-blue.png",true));
    }
  else if(hero->getClan() == gray)
    {
      life_symbol.setImage(loadImage("Images/Cards/Characters/life-gray.png",true));
    }
  life_symbol_empty.setImage(loadImage("Images/Cards/Characters/life-black.png", true));
  //to do, special fallen emperor som ska ha life-gold.png
 		       
  //get life colour depending on clan
  // hero->getClan();

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
	GameCard* lost_equipment = nullptr;
  
	switch(index)
	{
	case 0:
		lost_equipment = equipment.def_horse;
		break;
	case 1:
		lost_equipment = equipment.off_horse;
		break;
	case 2:
		lost_equipment = equipment.weapon;
		break;
	case 3:
		lost_equipment = equipment.shield;
		break;
	}
  // std::vector<GameCard*>::iterator it = eq.equipment.begin() + index;
  // eq.equipment.erase(it);

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
  // if(current_player == true)
    // {
  if(hero != nullptr)
    {
		for(auto i : hand)
		{
			i->paint(screen);
		}
		hero -> setPosition(870,551);
		hero -> paint(screen);

		 //ritar ut liv
		int x_offset_life = 872 + 30;
		int y_offset_life = 555 + 5;
		for(unsigned i = 0; i < max_life; ++i, x_offset_life += 17)
		  {
		    if(i < current_life)
		      {
			applySurface(x_offset_life, y_offset_life, life_symbol, screen);
		      }
		    else
		      {
			applySurface(x_offset_life, y_offset_life, life_symbol_empty, screen);
		      }
		    
		  }

     }
  
  //rita ut equipment
}

void Player::paint(Surface screen, int x_pos, int y_pos)
{
	if(hero != nullptr)
	{
	  hero->setPosition(x_pos, y_pos);
	  hero->paint(screen);
	  
	  //ritar ut liv
	  int x_offset_life = x_pos + 30;
	  int y_offset_life = y_pos + 5;
	  for(unsigned i = 0; i < max_life; ++i, x_offset_life += 17)
	    {
	      if(i < current_life)
		{
		  applySurface(x_offset_life, y_offset_life, life_symbol, screen);
		}
	      else
		{
		  applySurface(x_offset_life, y_offset_life, life_symbol_empty, screen);
		}
	      
	    }
	  //ritar ut ram om markerad
	  if(sel)
	    {
	      applySurface(x_pos-5, y_pos-5,selected_frame,screen);
	    }
	}
	//rita ut equipment

}

void Player::fixCardPosition()
{
  int x_pos = 161;
  int y_pos = 551;
  int offset;
  if(500/hand.size()-1 > 153)
    {
      offset = 153;
    }
  else
    {
      offset = 500/hand.size()-1;
    }
 
  for(auto i : hand)
    {
      i->setPosition(x_pos, y_pos);
      x_pos += offset;
    }
  hero->setPosition(8, 555);
}

bool Player::handleEvent(const SDL_Event& event)
{	
  if(hero != nullptr)
    {
	if(current_player)
	{
		for(unsigned i = 0; i < hand.size(); ++i)
		{
			hand.at(i) -> handleEvent(event);
		}
	}
	else
	{
		std::string com = "";
		if(hero != nullptr)
		  {
			com = hero -> handleEvent(event);
		  }
		if(com != "")
		  {

			return true;	//den blev fucking klickad!
		  }
	}
    }	
	return false;
}

void Player::setSelected(bool change_select)
{
  sel = change_select;
}



