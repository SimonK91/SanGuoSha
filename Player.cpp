#include "Player.h"


using namespace Object;

Player::Player() : role(-1),current_life(0),max_life(0), hero(nullptr)
{
  current_player = false;
  sel = false;
  selected_frame.setImage(loadImage("Images/Cards/Characters/hero-frame.png",true));
  //equipment.def_horse_pop->setText("hejsan hej");
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
  if(role == 0)
	++max_life;
  current_life = max_life;
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
  //rita ut handen längst ner på skärmen
  // if(current_player == true)
    // {
  if(hero != nullptr)
    {
      if(isCurrentPlayer() == true)
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
	  //rita ut equipment
	  if(equipment.weapon_image.getImage() != nullptr)
	    {
	      applySurface(5,550,equipment.weapon_image,screen);
	    }
	  if(equipment.shield_image.getImage() != nullptr)
	    {
	      applySurface(5,589,equipment.shield_image,screen);
	    }
	  if(equipment.def_horse_image.getImage() != nullptr)
	    {
	      applySurface(5,628,equipment.def_horse_image,screen);
	    }
	  if(equipment.off_horse_image.getImage() != nullptr)
	    {
	      applySurface(5,667,equipment.off_horse_image,screen);
	    }
	  
	  
	  equipment.def_horse_pop->paint(screen);
	  equipment.off_horse_pop->paint(screen);
	  equipment.weapon_pop->paint(screen);
	  equipment.shield_pop->paint(screen);
	  
	  
	}
      else
	{
	  hero->setPosition(player_x, player_y);
	  hero->paint(screen);
	      
	  //ritar ut liv
	  int x_offset_life = player_x + 30;
	  int y_offset_life = player_y + 5;
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
	      applySurface(player_x-5, player_y-5,selected_frame,screen);
	    }
	  
	  
	  if(equipment.weapon_image.getImage() != nullptr)
	    {
	      applySurface(player_x, player_y+50 ,equipment.weapon_image,screen);
	    }
	  if(equipment.shield_image.getImage() != nullptr)
	    {
	      applySurface(player_x,player_y + 89,equipment.shield_image,screen);
	    }
	  if(equipment.def_horse_image.getImage() != nullptr)
	    {
	      applySurface(player_x,player_y + 128,equipment.def_horse_image,screen);
	    }
	  if(equipment.off_horse_image.getImage() != nullptr)
	    {
	      applySurface(player_x,player_y + 167,equipment.off_horse_image,screen);
	    }
	  //rita ut popup text(den sköter kontroll om den ska ritas ut eller inte själv)
	  equipment.def_horse_pop->paint(screen);
	  equipment.off_horse_pop->paint(screen);
	  equipment.weapon_pop->paint(screen);
	  equipment.shield_pop->paint(screen);
	} 
      
    }
}

void Player::paint(Surface screen, int x_pos, int y_pos)
{
  /*
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
	*/
}

void Player::fixCardPosition()
{
	int active = -1;
	for (int i = 0 ; i < hand.size() ; ++i)
	{
		if(hand.at(i)->isActive())
			active = i;
	}
	
  double x_pos = 161;
  int y_pos = 551;
  double offset;
	if(hand.size() > 4 && ( active == -1 || hand.size()-1 == active)) // handen större än 4 OCH (inget kort är aktivt, eller sista kortet är aktivt)
		offset = 480 / (hand.size()-1.0);
	else if(hand.size() > 4)
		offset = (480 - 135) / (hand.size()-2.0);
	else
		offset = 153;
 
  for(int i = 0 ; i < hand.size() ; ++i)
    {
	  if(i != active)
	  {
        hand.at(i)->setPosition((int)x_pos, y_pos);
		x_pos += offset;
	  }
	  else if(hand.size() <= 4)
      {
	    hand.at(i)->setPosition((int)x_pos, y_pos-20);
		x_pos += offset;
	  }
	  else
      {
	    hand.at(i)->setPosition((int)x_pos, y_pos-20);
		x_pos += 135;
	  }
    }
	if(hero != nullptr)
		hero->setPosition(8, 555);	
}


bool Player::handleHand(const SDL_Event& event)
{
	for(int i = hand.size()-1 ; i >= 0 ; --i)
	{
		if(hand.at(i) -> handleEvent(event) != "")
		{
			SDL_Event event2 = event;
			event2.motion.x = -100;
			event2.motion.y = -100;
			for(int j = i-1 ; j >= 0 ; --j)
				hand.at(j) -> handleEvent(event2);
			return true;
		}
	}
	return false;
}
bool Player::handleEvent(const SDL_Event& event)
{	
  if(hero != nullptr)
    {
		if(!current_player)
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
			equipment.def_horse_pop->handleEvent(event);
			equipment.off_horse_pop->handleEvent(event);
			equipment.weapon_pop->handleEvent(event);
			equipment.shield_pop->handleEvent(event);
		}
		if(isCurrentPlayer() == true)
		  {
		    std::cout << "hest event" << std::endl;
		    equipment.def_horse_pop->handleEvent(event);
		    equipment.off_horse_pop->handleEvent(event);
		    equipment.weapon_pop->handleEvent(event);
		    equipment.shield_pop->handleEvent(event);
		  }
    }	
	return false;
}

void Player::setSelected(bool change_select)
{
  sel = change_select;
}


Object::GameCard* Player::equipStuff(GameCard* gear)
{
  std::cout << "Vi ska equippa: " << gear->getAbility() << std::endl;
  std::cout << "ID 6 tecken: " << gear->getAbility().substr(6,6) << std::endl;
  std::cout << "ID 9 tecken: " << gear->getAbility().substr(6,9) << std::endl;
  
  if(gear->getAbility().substr(6,6) == "weapon")
    {

      std::cout << gear->getAbility().substr(13,10) << std:: endl;

      
      //equipment.weapon_pop->setText("VAPEN DO DMG AND WIN");
       equipment.weapon_pop->setFileText("Data/equipment.txt", gear->getAbility().substr(13,10));
      if(equipment.weapon_image.getImage() == nullptr)
	{
	  equipment.weapon_image.setImage(loadImage("Images/Gui/weapon.png"));
	}
      if(equipment.weapon == nullptr)
	{
	  std::swap(equipment.weapon, gear);
	  return gear;
	}
      else
	{
	  equipment.weapon = gear;
	  return nullptr;
	}
    }
  else if(gear->getAbility().substr(6,6) == "shield")
    {
      equipment.shield_pop->setText("shield, describe how it works");
      if(equipment.shield_image.getImage() == nullptr)
	{
	  equipment.shield_image.setImage(loadImage("Images/Gui/shield.png"));
	}
      if(equipment.shield == nullptr)
	{
	  std::swap(equipment.shield, gear);
	  return gear;
	}
      else
	{
	  equipment.shield = gear;
	  return nullptr;
	}
    }
  else if(gear->getAbility().substr(6,9) == "off_horse")
    {
      equipment.off_horse_pop->setText("offensive horse, fuck you horse");
      if(equipment.off_horse_image.getImage() == nullptr)
	{
	  equipment.off_horse_image.setImage(loadImage("Images/Gui/offensive-horse.png"));
	}
      if(equipment.off_horse == nullptr)
	{
	  std::swap(equipment.off_horse, gear);
	  return gear;
	}
      else
	{
	  equipment.off_horse = gear;
	  return nullptr;
	}
    }
  else if(gear->getAbility().substr(6,9) == "def_horse")
    {
      equipment.def_horse_pop->setText("why so defensive");
      if(equipment.def_horse_image.getImage() == nullptr)
	{
	  equipment.def_horse_image.setImage(loadImage("Images/Gui/defensive-horse.png"));					    
	}
      if(equipment.def_horse == nullptr)
	{
	  std::swap(equipment.def_horse, gear);
	  return gear;
	}
      else
	{
	  equipment.def_horse = gear;
	  return nullptr;
	}
    }

  //något gick snett(vi fick en en equipment som inte är vapen/shield/off_horse/def_horse
  return nullptr;
}

void Player::setPos(int x_pos, int y_pos)
{
  player_x = x_pos;
  player_y = y_pos;
  
  if(isCurrentPlayer() == true)
    {
      equipment.weapon_pop->setPos(5,550);
      equipment.shield_pop->setPos(5,589);
      equipment.def_horse_pop->setPos(5,628);
      equipment.off_horse_pop->setPos(5,667);
    

    }
  else
    {
      equipment.def_horse_pop->setPos(x_pos + 5 ,y_pos + 50);
      equipment.off_horse_pop->setPos(x_pos + 5, y_pos + 89);
      equipment.weapon_pop->setPos(x_pos + 5, y_pos + 128);
      equipment.shield_pop->setPos(x_pos + 5, y_pos + 167);
    }
  
}

void Player::setCurrentPlayer(bool cp)
{
  current_player = cp;
  
  equipment.weapon_pop->setPos(5,550);
  equipment.shield_pop->setPos(5,589);
  equipment.def_horse_pop->setPos(5,628);
  equipment.off_horse_pop->setPos(5,667);
  
}

