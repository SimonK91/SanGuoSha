#include "SGS.h"

//constructor
Game::Game() : card_deck("standard_playing_cards"),discard_pile("empty")
{

}


bool Game::Setup()
{
//step 1)
//wait for everyone to enter

//step 2)
//shuffle role cards

//step 3)
//distribute role cards

//step 4)
//announce emperor

//step 5)
//shuffle character cards

//step 6)
//give emperor 5 characters to choose between

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
bool Game::run()
{

}