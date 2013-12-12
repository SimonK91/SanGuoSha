#include "Player.h"


using namespace Object;

Player::Player(const std::string& name_) : role(-1),current_life(0),max_life(0), hero(nullptr)
{
  current_player = false;
  sel = false;
  selected_frame.setImage(loadImage("Images/Cards/Characters/hero-frame.png",true));
  
  TTF_Font* font = TTF_OpenFont("Fonts/LHANDW.TTF",13);
  name = TTF_RenderText_Blended(font,name_.c_str(),{255,255,255,0});	//skapa en yta med namnet
  
  cleanUp({font});
  hero_frame.setImage(loadImage("Images/Gui/heroFrame.png",true));
  
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
    {
      ++max_life;
    }
  current_life = max_life;
  male = character->getMale();
  hero = character;
  alive = true;
  hero_profile.setImage(loadImage("Images/Cards/Characters/"+character->getFileName()));

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
}
void Player::setRole(int r)
{
  role = r;
  if(r == 0)
    {
      player_role.setImage(loadImage("Images/Gui/emperor.png", true));
    }
  else if(r == 1)
    {
      player_role.setImage(loadImage("Images/Gui/loyal.png", true));
    }
  else if(r == 2)
    {
      player_role.setImage(loadImage("Images/Gui/spy.png", true));
    }
  else  if(r == 3)
    {
      player_role.setImage(loadImage("Images/Gui/rebel.png", true));
    }
  
}

GameCard* Player::playCard(int index)
{

  	GameCard* played_card = nullptr;
	
	if(index < hand.size())
	{
		played_card = hand.at(index);
		std::vector<GameCard*>::iterator it = hand.begin() + index;
		hand.erase(it);
  
		fixCardPosition();
	}
	return played_card;
}

GameCard* Player::loseCard(int index)
{
	GameCard* lost_card = nullptr;
	
	if(index < hand.size())
	{
		lost_card = hand.at(index);
		std::vector<GameCard*>::iterator it = hand.begin() + index;
		hand.erase(it);
  
		fixCardPosition();
	}
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
      equipment.def_horse = nullptr;
      equipment.def_horse_image.clean();
      equipment.def_horse_image_thin.clean();
      break;
    case 1:
      lost_equipment = equipment.off_horse;
      equipment.off_horse_image.clean();
      equipment.off_horse_image_thin.clean();
      equipment.off_horse = nullptr;
      break;
    case 2:
      lost_equipment = equipment.weapon;
      equipment.weapon_image.clean();
      equipment.weapon_image_thin.clean();
      equipment.weapon = nullptr;
      break;
    case 3:
      lost_equipment = equipment.shield;
      equipment.shield_image.clean();
      equipment.shield_image_thin.clean();
      equipment.shield = nullptr;
      break;
    }
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
  if(hero != nullptr)
    {
      hero -> setPosition(870,551);
      hero -> paint(screen);
      for(auto i : hand)
	{
	  i->paint(screen);
	}
      applySurface(970,540,player_role,screen);
      //ritar ut liv
      int x_offset_life = 872 + 30;
      int y_offset_life = 555 + 5;
      for(int i = 0; i < max_life; ++i, x_offset_life += 17)
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
      applySurface(876,555,name,screen);
      
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
    }
}

void Player::paint(Surface screen, int x_pos, int y_pos)
{
  if(hero != nullptr)
    {
      hero->setPosition(x_pos, y_pos);
      applySurface(x_pos, y_pos, hero_profile,screen);
      applySurface(x_pos-3, y_pos-4,hero_frame,screen);

      //ritar ut liv
      int x_offset_life = x_pos + 70;
      int y_offset_life = y_pos + 80;
      for(int i = 0; i < max_life; ++i, x_offset_life += 14)
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
      applySurface(x_pos+5,y_pos,name,screen);
    }

  if(equipment.weapon_image_thin.getImage() != nullptr)
    {
      applySurface(player_x+1, player_y+ 100,equipment.weapon_image_thin,screen);
    }
  if(equipment.shield_image_thin.getImage() != nullptr)
    {
      applySurface(player_x+1,player_y + 126,equipment.shield_image_thin,screen);
    }
  if(equipment.def_horse_image_thin.getImage() != nullptr)
    {
      applySurface(player_x+1,player_y + 153,equipment.def_horse_image_thin,screen);
    }
  if(equipment.off_horse_image_thin.getImage() != nullptr)
    {
      applySurface(player_x+1,player_y + 179,equipment.off_horse_image_thin,screen);
    }    
}

void Player::fixCardPosition()
{
  int active = -1;
  for (unsigned i = 0 ; i < hand.size() ; ++i)
    {
      if(hand.at(i)->isActive())
	{
	  active = i;
	}
    }
  
  double x_pos = 161;
  int y_pos = 551;
  double offset;
  if(hand.size() > 4 && ( active == -1 || (int)(hand.size()-1) == active))    
    {
      offset = 480 / (hand.size()-1.0);
    }
  else if(hand.size() > 4)
    {
      offset = (480 - 135) / (hand.size()-2.0);
    }
  else
    {
      offset = 153;
    }

  for(unsigned i = 0 ; i < hand.size() ; ++i)
    {
      if(i != (unsigned)active)
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
    {
      hero->setPosition(8, 555);
    }	
}


Object::GameCard* Player::handleHand(const SDL_Event& event)
{
  for(int i = hand.size()-1 ; i >= 0 ; --i)
    {
      if(hand.at(i) -> handleEvent(event) != "")
	{
	  SDL_Event event2 = event;
	  event2.motion.x = -100;
	  event2.motion.y = -100;
	  for(int j = i-1 ; j >= 0 ; --j)
	    {
	      hand.at(j) -> handleEvent(event2);
	    }
	  fixCardPosition();
	  return hand.at(i);
	}
    }
  return nullptr;
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
	}
      else
	{
	}
      equipment.def_horse_pop->handleEvent(event);
      equipment.off_horse_pop->handleEvent(event);
      equipment.weapon_pop->handleEvent(event);
      equipment.shield_pop->handleEvent(event);
    }
 
  return false;
}

void Player::setSelected(bool change_select)
{
  sel = change_select;
  if(change_select)
    hero->setActive(1);
  else
    hero->setActive(0);
}

Object::GameCard* Player::equipStuff(GameCard* gear, int type)
{
  Surface tmp_range_surface;
  std::string weapon_range = I2S(gear->getRange());
  std::cerr << gear->getAbility() << std::endl;
  //std::string weapon_range = "5";
  tmp_range_surface = textToSurface(weapon_range,"Fonts/arial.ttf", 15);
  
  if(type == 1)
    {
      equipment.weapon_pop->setText("VAPEN DO DMG AND WIN");
      // equipment.weapon_pop->setFileText("Data/equipment.txt", gear->getAbility().substr(13,10));
      if(equipment.weapon_image.getImage() == nullptr)
	{
	  equipment.weapon_image.setImage(loadImage("Images/Gui/weapon.png"));
	  applySurface(0,0,tmp_range_surface,equipment.weapon_image);
	  equipment.weapon_image_thin.setImage(loadImage("Images/Gui/weapon-thin.png"));
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
  else if(type == 2)
    {
      equipment.shield_pop->setText("shield, describe how it works");
      if(equipment.shield_image.getImage() == nullptr)
	{
	  equipment.shield_image.setImage(loadImage("Images/Gui/shield.png"));
	  equipment.shield_image_thin.setImage(loadImage("Images/Gui/shield-thin.png"));
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
  else if(type == 3)
    {
      equipment.off_horse_pop->setText("offensive horse, fuck you horse");
      if(equipment.off_horse_image.getImage() == nullptr)
	{
	  equipment.off_horse_image.setImage(loadImage("Images/Gui/offensive-horse.png"));
	  equipment.off_horse_image_thin.setImage(loadImage("Images/Gui/offensive-horse-thin.png"));
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
  else if(type == 4)
    {
      equipment.def_horse_pop->setText("why so defensive");
      if(equipment.def_horse_image.getImage() == nullptr)
	{
	  equipment.def_horse_image.setImage(loadImage("Images/Gui/defensive-horse.png"));
	  equipment.def_horse_image_thin.setImage(loadImage("Images/Gui/defensive-horse-thin.png"));					    
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
  std::cerr << "något gick snett(vi fick en en equipment som inte är vapen/shield/off_horse/def_horse" << std::endl;
  return nullptr;
}

void Player::showToolTip(Surface screen)
{
  equipment.def_horse_pop->paint(screen);
  equipment.off_horse_pop->paint(screen);
  equipment.weapon_pop->paint(screen);
  equipment.shield_pop->paint(screen);
  if(isCurrentPlayer() == true)
    {
      for(GameCard* g : hand)
	{
	  g->showToolTip(screen);
	}
  }
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
      equipment.def_horse_pop->setPos(x_pos + 5 ,y_pos + 153);
      equipment.off_horse_pop->setPos(x_pos + 5, y_pos + 179);
      equipment.weapon_pop->setPos(x_pos + 5, y_pos + 100);
      equipment.shield_pop->setPos(x_pos + 5, y_pos + 126);
    }
}

void Player::handleToolTip(SDL_Event& event)
{
  for(GameCard* g : hand)
    {
      g->toolEvent(event);
    }  
}

bool Player::hasAcedia()
{
	if(judgement_cards.size() == 0)
		return false;
	if(judgement_cards.top() -> getAbility() == "acedia" || judgement_cards.size() == 2)
		return true;
	return false;
}

bool Player::hasLightning()
{
	if(judgement_cards.size() == 0)
		return false;
	if(judgement_cards.top() -> getAbility() == "lightning" || judgement_cards.size() == 2)
		return true;
	return false;
}
