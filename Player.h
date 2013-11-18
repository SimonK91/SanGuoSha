#include "CardList.h"
#include <string>
#include <stack>


enum Equipment{Weapon,Shield,off_horse,def_horse};


class Player
{
private:
	int role;
	int current_life;
	int max_life;
	bool male;
	int game_status;
	Object::CardList hand;
	Equipment equipment;
	Object::HeroCard hero;
	std::stack<Object::GameCard> judgement_cards;
public:
	Player() = default;
	~Player() = default;
	Object::Card* playCard(int index);
	void receiveCard(Object::Card* what_card);
	Object::Card* loseCard(int index);
	Object::Card* loseEquipment(int index);
	void setHero(Object::HeroCard* character);
	void doEffect(std::string what_effect);
	
	bool entered(){return game_status == 1;}
	bool loading(){return game_status == 0;}
	bool left()   {return game_status == 2;}
	void set_status(unsigned i){if (i <=2){game_status = i;}}
	void paint();

};