#include "SGS.h"
#include <chrono>
#include <algorithm>

using namespace Object;

void Game::setup()
{
	std::vector<int> role{0,2,3,1,3,3,3,1,1,2};
	unsigned emperor = 0;
	unsigned step = 1;
//step 1)
//wait for everyone to enter
	if(step == 1)
	{
		step = 2;
		
		for(unsigned i = 0; i < players.size() ; ++i)
		{
			if(!players.at(i).entered())
				step = 1;
		}
	}
//step 2)
//shuffle role cards
	else if(step == 2)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle (role.begin(), role.begin()+players.size()-1, std::default_random_engine(seed));
		step = 3;
	}
//step 3)
//distribute role cards
	else if(step == 3)
	{
		for(unsigned i = 0; i < players.size() ; ++i)
		{
			//players.at(i).set_role() = role.at(i);
			if(role.at(i) == 0)
				emperor = i+1;
		}
		step = 5; //skip announcement
	}
	
//step 4)
//announce emperor
/*	for(unsigned i = 0; i < players.size() ; ++i)
	{
		if(players.at(i).get_role() == 0)
		{
			makeTimedtext("Player: " + players.at(i).get_name() + " is the emperor.",300,300,3000)
		}*/
//step 5)
//shuffle character cards
//and give emperor 5 characters to choose between
	else if(step == 5)
	{
		hero_deck.shuffle();
	
		Window* characters = new Window(200,200,400,300);
		delete characters;
	
	}
	

//step 7)
//announce emperor's character

//step 8)
//shuffle all remaining characters

//step 9)
//give everyone else 3 characters to choose between

//step 10)
//distribute 4 playing cards to each player

//step 11)
//start the game
}

void Game::game()
{
//phase 1)
//start of turn
//special hero abilities trigger here

//phase 2
//judgement phase
//pending cards activate in stacked order
//negate can remove pending card
//else judge

//phase 3
//drawing phase
//special hero abilities trigger here
//draw 2 cards

//phase 4
//action phase
//many hero abilities available
//on-hand cards can be used
//max 1 attack unless buff active

//phase 5
//discard phase
//lü meng ability active here
//on-hand cards have to be same as current life
//other cards are discarded

//phase 6
//ending phase
//special hero abilities can trigger here (shapeshifter, diao chan

//next player, start from phase 1

//if a player dies, check for winning conditions
//if an equipment is added/removed, update player stats
//if a card is active, check rule-book for targets
//if a valid target is selected, activate button "play card"
//if a player is targetted by an effect, check possible plays.
//if a tool-card is played, check every player for negate card.

}



void Game::end()
{
//show score-table
//keep chat open
//make exit button

}
void Game::run()
{

}

#include "game_commands.cpp"