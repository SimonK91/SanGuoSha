#include "Player.h"
/*
	int current_life;
	int max_life;
	CardList hand;
	Equipment equipment;
	HeroCard hero;
	stack<GameCard> judgement_cards;
*/

	Card* Player::playCard(int index)
	void Player::receiveCard(Card* what_card)
	Card* Player::loseCard(int index)
	Card* Player::loseEquipment(int index)
	void Player::setHero(HeroCard* character)
	{
		current_life = character -> getHP();
		max_life = current_life;
		male = character -> getMale();
		
	void Player::doEffect(string what_effect)
	void Player::paint()
