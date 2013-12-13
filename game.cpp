#include "SGS.h"
#include <chrono>
#include <algorithm>

using namespace Object;

void Game::setupHotseat()
{
  run_command("set_settings");

	run_next = true;
	std::vector<int> role{0,2,3,1,3,3,1,3,1,2};
	int emperor = -1;
	unsigned step = 1;
	
	while(running)
	{
	
	// //step 1)
	// //shuffle role cards
		if(step == 1)
		{
		
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle (role.begin(), role.begin()+players.size(), std::default_random_engine(seed));
			
			step = 2;
		}
		
		
	// //step 2)
	// //distribute role cards
		else if(step == 2)
		{
		
			for(unsigned i = 0; i < players.size() ; ++i)
			{
				players.at(i)->setRole(role.at(i));
				
				if(role.at(i) == 0)
					emperor = i;
			}
			step = 3;
		}
	//step 3)
	//shuffle character cards
	//and give emperor 5 characters to choose between
		else if(step == 3)
		{
		
			Card* hero1 = hero_deck->drawCard(); //the three emperors
			Card* hero2 = hero_deck->drawCard();
			Card* hero3 = hero_deck->drawCard();
			std::cout << "Emperor-cards drawn" << std::endl;	
			
			hero_deck->shuffle();
			std::cout << "hero_deck shuffled" << std::endl;
			
			Card* hero4 = hero_deck->drawCard();
			Card* hero5 = hero_deck->drawCard();
			std::cout << "two more cards drawn" << std::endl;
			
			has_window = true;
			Window* characters = new Window(80,50,510,470);
			characters->addCard(hero1,20,30);
			characters->addCard(hero2,180,30);
			characters->addCard(hero3,340,30);
			characters->addCard(hero4,25,250);
			characters->addCard(hero5,190,250);
			characters->makeButton("Choose",365,320,"pick_hero","Images/Gui/mediumButton.png");
			add_window(characters);
			step = 4;
			self = emperor;
		}
	

		//step 4)
		//wait for emperor to choose character
		else if(step == 4)
		{
			if(players.at(emperor)->hasHero())
			{
				step = 5;
			}
		}

	//step 5)
	//shuffle all remaining characters
		else if(step == 5)
		{
			for(int i = 0 ; i < 5 ; ++i)
			{
				hero_deck->shuffle();
				SDL_Delay(2);
			}
			step = 6;
		}

	//step 6)
	//give everyone else 3 characters to choose between
		else if(step == 6)
		{
			++self;
			if(self == players.size())
				self = 0;
		
			if((int)self == emperor)
				step = 8;
			else
			{
				Card* hero1 = hero_deck->drawCard();
				Card* hero2 = hero_deck->drawCard();
				Card* hero3 = hero_deck->drawCard();
				
				has_window = true;
				Window* characters = new Window(100,100,500,350);
				characters->addCard(hero1,15,40);
				characters->addCard(hero2,170,40);
				characters->addCard(hero3,335,40);
				characters->makeButton("Choose",300,270,"pick_hero","Images/Gui/mediumButton.png");
				add_window(characters);
				
				step = 7;
			}
		}

	//step 7)
	//wait for everyone to have chosen a character
		else if(step == 7)
		{
			if(players.at(self)->hasHero())
				step = 6;
		}
	//step 8)
	//distribute 4 playing cards to each player
		else if(step == 8)
		{
			card_deck->shuffle();
			for(auto p : players)
			{
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
			}
			step = 9;
		}

	//step 9)
	//start the game
		else if(step == 9)
		{
			return;
		}

	//skriver ut UI:t
		UI();
	}
}


void Game::setup()
{
	run_next = true;
	std::vector<int> role{0,2,3,1,3,3,1,3,1,2};
	int emperor = -1;
	unsigned step = 1;
	//players.at(1)->setStatus(1);
	
	while(running)
	{
		//step 1)
		//wait for everyone to enter
		if(step == 1)
		{
		
			step = 2;
			for(unsigned i = 0; i < players.size() ; ++i)
			{
				if(!players.at(i)->entered())
				{
					step = 1;
				}
			}
		}
		
	// //step 2)
	// //shuffle role cards
		else if(step == 2)
		{
		
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle (role.begin(), role.begin()+players.size(), std::default_random_engine(seed));
			
			step = 3;
		}
		
		
	// //step 3)
	// //distribute role cards
		else if(step == 3)
		{
		
			for(unsigned i = 0; i < players.size() ; ++i)
			{
				players.at(i)->setRole(role.at(i));
				
				if(role.at(i) == 0)
					emperor = i;
			}
			step = 4;
		}
	//step 4)
	//shuffle character cards
	//and give emperor 5 characters to choose between
		else if(step == 4)
		{
		
			Card* hero1 = hero_deck->drawCard(); //the three emperors
			Card* hero2 = hero_deck->drawCard();
			Card* hero3 = hero_deck->drawCard();
			std::cerr << "Emperor-cards drawn" << std::endl;	
			
			hero_deck->shuffle();
			std::cerr << "hero_deck shuffled" << std::endl;
			
			Card* hero4 = hero_deck->drawCard();
			Card* hero5 = hero_deck->drawCard();
			std::cerr << "two more cards drawn" << std::endl;
			
			if(emperor == (int)self)
			{
				has_window = true;
				Window* characters = new Window(100,100,600,550);
				characters->addCard(hero1,0,0);
				characters->addCard(hero2,200,0);
				characters->addCard(hero3,400,0);
				characters->addCard(hero4,100,250);
				characters->addCard(hero5,300,250);
				characters->makeButton("Choose",0,500,"pick_hero");
				add_window(characters);
			}
			step = 6;
		}
	

	//step 6)
	//wait for emperor to choose character
	else if(step == 6)
	{
		if(players.at(emperor)->hasHero())
		{
			step = 8;
		}
	}

//step 7)
//announce emperor's character

//step 8)
//shuffle all remaining characters
	else if(step == 8)
	{
		for(int i = 0 ; i < 5 ; ++i)
		{
			hero_deck->shuffle();
			SDL_Delay(2);
		}
		step = 9;
	}

//step 9)
//give everyone else 3 characters to choose between
	else if(step == 9)
	{
		//for(unsigned i = 0 ; i < players.size() ; ++i)
		//{
						
			if(!players.at(self)->hasHero())
			{
				Card* hero1 = hero_deck->drawCard();
				Card* hero2 = hero_deck->drawCard();
				Card* hero3 = hero_deck->drawCard();
				Window* characters = new Window(100,100,600,550);
				characters->addCard(hero1,0,0);
				characters->addCard(hero2,200,0);
				characters->addCard(hero3,400,0);
				characters->makeButton("Choose",0,500,"pick_hero");
				if(self == self)
					add_window(characters);
				else
					delete characters;
				//break;
			}
		// }
		step = 10;
	}

//step 10)
//wait for everyone to have chosen a character
	else if(step == 10)
	{
		step = 11;
		for(auto p : players)
			if(!p->hasHero())
				step = 10;
		

	}
//step 10)
//distribute 4 playing cards to each player
		else if(step == 11)
		{
			card_deck->shuffle();
			for(auto p : players)
			{
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
				p->recieveCard(dynamic_cast<GameCard*>(card_deck->drawCard()));
			}
			step = 12;
		}

//step 11)
//start the game
		else if(step == 12)
			return;

			
		// std::cerr << "painting" << std::endl;
		UI();
		// std::cerr << "post painting" << std::endl;
	}
	
	//return run_next;
}

void Game::runHotseat()
{
	game_stage = 1;
	// card_deck -> shuffle();
	
	// //simulerade spelare:
	// Player* player = new Player();
	// player -> setRole(0); //emparor
	// player -> setHero(new HeroCard("CaoCao.png", "4 blue 1 ability"));
	// players.push_back(player);
	
	// player = new Player();
	// player -> setRole(1); 
	// player -> setHero(new HeroCard("DiaoChan.png", "3 gray 0 ability"));
	// players.push_back(player);
	
	// player = new Player();
	// player -> setRole(2);
	// player -> setHero(new HeroCard("DaQiao.png", "3 green 0 ability"));
	// players.push_back(player);
	
	// player = new Player();
	// player -> setRole(2);
	// player -> setHero(new HeroCard("ElderZhuge.png", "3 red 1 ability"));
	// players.push_back(player);	
	// player = nullptr;
	
	// running = true;
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	// card_deck -> pushTop(new GameCard(11,hearts,"draw2.png","draw2 0 0")); //ability id, target type, target range
	card_deck -> pushTop(new GameCard(5,hearts,"unicorn_bow.png",					"weapon4 5 5")); //ability id, target type, target range
	card_deck -> pushTop(new GameCard(13,spades,"da_wan.png","off_horse 5 0")); //ability id, target type, target range
	card_deck -> pushTop(new GameCard(1,clubs,"frost_blade.png",					"weapon8 5 2")); //ability id, target type, target range


	GameCard* card = nullptr;
	Window* nextPlayer_window = new Window(270,350,300,150);
	nextPlayer_window -> makeTextbox(40,25,220,30,17);
	nextPlayer_window -> setText(0, "Next player's turn");
	nextPlayer_window -> makeButton("OK!",45,70,"next_state");
	running = true;
	state = -1;
	bool isInAcedia;
	while(running)
	{
	//phase -1)
	//change of player
		if(state == -1)
		{
			has_attacked = false;
			isInAcedia = false;
			players.at(self) -> setCurrentPlayer(true);
			current_player = players.at(self);
			for(auto p : players)
			{
			    p->setSelected(false);
			}
			has_window = true;
			add_window(nextPlayer_window);
			++state;
			if(timer->checkStarted() == true)
			  {
			    timer->stop();
			  }
			
		
		}
	
	//phase 0)
	//go past OK screen
		if(state == 0)
		{
			//happens through button click
		}
		
		std::string cmp = timer->time_ran_out();
		if(cmp != "")
		  {
		    std::cout << "Kor kommandot: " << cmp << std::endl;
		    run_command(cmp);
		    //timer->stop();
		  }
	//phase 1)
	//start of turn
	//special hero abilities trigger here
		// std::cout << "the state: " << state << std::endl;
		else if(state == 1)
		{
		  //timer
		  timer->start(sett.getTimerTime());
		   timer->setCommand("end_turn");
		   m.playSoundEffect(8);
		  state = 2;
		}
	//phase 2
	//judgement phase
	//pending cards activate in stacked order
	//negate can remove pending card
	//else judge
		else if(state == 2)
		{
			GameCard* judgement;
			do
			{
				judgement = current_player -> getJudgementCard();
				if(judgement != nullptr)
				{
					if(judgement -> getAbility() == "acedia")
					{
						isInAcedia = acedia();
						discard_pile -> pushBottom(judgement);
					}
					else if(judgement -> getAbility() == "lightning")
					{
						if(lightningExplode())
						{
							modifyLife(current_player,-1);
							discard_pile -> pushBottom(judgement);
						}
						else
						{
							int newLightningTarget = self;
							do
							{
								newLightningTarget = nextPlayer(newLightningTarget);
							}while(players.at(newLightningTarget) -> hasLightning());
							
							players.at(newLightningTarget) -> addJudgementCard(judgement);
						}	
					}
				}
			}while(judgement != nullptr);
			state = 3;
		}
	//phase 3
	//drawing phase
	//special hero abilities trigger here
	//draw 2 cards
		else if(state == 3)
		{
				
			//draw 2 cards
			for(int i = 0 ; i < 2 ; ++i)
			{
				if(card_deck -> empty())
				{
					std::swap(card_deck,discard_pile);
					card_deck -> shuffle();
				}
				if(card_deck -> empty())
					throw SGS_error("card deck and discard deck totally empty!");
				else
				{
					card = dynamic_cast<GameCard*>(card_deck -> drawCard());
					players.at(self) -> recieveCard(card);
				}
			}
				/*
				<insert hero abilitys here>
				*/
			if(!isInAcedia)
				state = 4; //  action phase
			else
				state = 5; // discard phase
		}
		
	//phase 4
	//action phase
	//many hero abilities available
	//on-hand cards can be used
	//max 1 attack unless buff active

		else if(state == 4)
		{
			
			//do stuff :D 		
			//preferebly whit the buttons :D
		}
	//phase 5
	//discard phase
	//lü meng ability active here
	//on-hand cards have to be same as current life
	//other cards are discarded
		else if(state == 5)
		{
			if(players.at(self) -> getLife() >= (int)(players.at(self) -> getHandSize()))
			{
				state = 6;
			}
		}

	//phase 6
	//ending phase
	//special hero abilities can trigger here (shapeshifter, diao chan
	
		else if(state == 6)
		{	
			players.at(self) -> setCurrentPlayer(false);
			self = nextPlayer();
			state = -1;
			target_player.clear();
			
		}
		//steal / dismantle phase
		else if(state == 7)
		  {
		    
		  }
		//	std::cout << "state:" << state << std::endl;
		// if(i == 1)
		// {
			// //winning test!
		// }
	//next player, start from phase 1

		UI(); //call the UI for repaint
	}//player loop
	
//if a player dies, check for winning conditions
//if an equipment is added/removed, update player stats
//if a card is active, check rule-book for targets
//if a valid target is selected, activate button "play card"
//if a player is targetted by an effect, check possible plays.
//if a tool-card is played, check every player for negate card.

	//return run_next;
	delete nextPlayer_window;
}

void Game::end(int winner)
{
	Window winning_screen(50,50,500,500);
	winning_screen.makeTextbox(30,30,440,300,30);
	winning_screen.makeButton("Exit",30,430,"close");
	
	if(winner == 1)
	{
		winning_screen.setText(0,"Congratulations, the winner of this match is the emperor and loyals!");
	}
	else if(winner == 2)
	{
		winning_screen.setText(0,"The amazing Spy managed to trick everyone and has now taken the spot as a ruler of this infected kingdom.");
	}
	else if(winner == 3)
	{
		winning_screen.setText(0,"The rebels made an uproar agains the empire and managed to storm the capital. Killing the Emperor and has no ruler anymore");
	}
	else if(winner == 4)
	{
		winning_screen.setText(0,"Without an Emperor to rule the kingdom, chaos arrived. Loyals and Spies fighting eachother without any results.");
	}
	
	
	bool has_window = true;
		while(has_window && running)
		{
			while(SDL_PollEvent( &event))
			{
			  exitCommand(event);
				if(winning_screen.handleEvent(event) == "close")
				{
					has_window = false;
					running = false;
				}
				
			}
			//måla lite fint
			paint();
			
			winning_screen.paint(screen);
			SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
			fps.regulateFPS();
		}
	
	
	
//show score-table
//keep chat open
//make exit button
	//return true; //:D
}

bool Game::exit()
{
	//clean up everything!!
	try
	{
	// writeSettings(settings);
		int nObjects = 0;
		while(!all_objects.empty())
		{
			delete all_objects.back();
			all_objects.pop_back();
			nObjects++;
		}
		std::cerr << "nObjects deleted: " << nObjects << std::endl;
		nObjects = 0;
		while(!players.empty())
		{
			delete players.back();
			players.pop_back();
			nObjects++;
		}
		std::cerr << "players deleted: " << nObjects << std::endl;
		delete card_deck;
		delete hero_deck;
		delete discard_pile;
	}
	catch(...)
	{
		return false;
	}
	std::cerr << "clean up was done!" << std::endl;
	return true;
}

void Game::UI()
{
	
	std::string command = "";
	static Button play_button("Play", 800, 575, "play_card","Images/Gui/smallButton.png",20);
	static Button end_button("End", 800, 630, "end_turn","Images/Gui/smallButton.png",20);
	static Button discard_button("Disc",800, 575, "discard_card","Images/Gui/smallButton.png",20);

	fps.start();
	while( SDL_PollEvent( &event)) //sÃ¥ lÃ¤nge som det finns en event
	{
		for(unsigned i = 0 ; i < all_objects.size() ; ++i)  //fÃ¶r varje objekt som finns i gamestatet
		{
			 //om objektet Ã¤r ett aktivt objekt och has_window är false(aktiva objekt kan manipulera saker)
			if(!has_window && dynamic_cast<ActiveObject*>(all_objects.at(i)) != nullptr)
			{
				 //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
				command = dynamic_cast<ActiveObject*>(all_objects.at(i))->handleEvent(event);
				run_command(command);
			}
			 //annars kör enbart handle_event på window
			else if(has_window && dynamic_cast<Window*>(all_objects.at(i)) != nullptr)
			{
				command = dynamic_cast<Window*>(all_objects.at(i))->handleEvent(event); //kÃ¶r handle event pÃ¥ objektet (detta ser om kriterier Ã¤r uppfyllda fÃ¶r att gÃ¶ra nÃ¥got
				run_command(command);
			}
		}
		if(state == 5)
		  run_command(discard_button.handleEvent(event));
		

		if(game_stage == 1)
		  {
			std::string button_command;
		    //kolla om någon av knapparna trycks!
			if(state == 4)
			{
				button_command = play_button.handleEvent(event);
				if(button_command != "")
				{
					if(rulePlayCardOK())
						run_command(button_command);
				}
				else
				{
					button_command = end_button.handleEvent(event);
					if(button_command != "")
					{
						SDL_Event temp_event = event;
						temp_event.motion.x = -100;
						temp_event.motion.y = -100;
						current_player -> handleHand(temp_event);
						run_command(button_command);
					}
				}
			}
		    
		    if(event.type != SDL_MOUSEBUTTONUP)
		      {
			for(Player* p : players)
			  {
			    p->handleEvent(event);
			    p->handleToolTip(event);
			  }
		      }
		  
		//kolla spelare och nuvarande handen
		    if(event.type == SDL_MOUSEBUTTONUP && !has_window && game_stage == 1)
		      {
			//om inte en knapp trycktes in, gör detta!
			if(button_command == "")
			  {
			    bool player_pressed = false;
			    
			    //fixa med players o deras event!
			    
			    for(Player* p : players)
			      {
					if(p -> handleEvent(event))
					{
						if(ruleTargetOK(p))
						{
							target_player.push_back(p);
							p->setSelected(true);
							player_pressed = true;
						}
				    break;
				  }
				// else if(target_player.size() != 0 && source_player == nullptr && target_player.at(0) != p && p -> handleEvent(event))
				  // {
				    // source_player = target_player;
				    // target_player = p;
				    // p-> setSelected(true);
				    // player_pressed = true;
				    // break;
				  // }
			      }
			    //rensa selection
			    if(!player_pressed)
			      {
				for(Player* p : players)
				  {
				    p->setSelected(false);
				  }
				// target_player = nullptr;
				target_player.clear();
				source_player = nullptr;
			      }
			    //om varken player eller knappar är tryckta, kolla om kort i hand är tryckta
			    if(!player_pressed && button_command == "")
			      {
				selected_card = nullptr;
				if(current_player != nullptr)
				  selected_card = current_player -> handleHand(event);
				std::cerr << "selected card: " << std::boolalpha << (selected_card == nullptr) << std::endl;
			      }
			  }
		      }
		  }
		// om krysset uppe till hÃ¶ger eller alt + F4 blev intryckt
		if( event.type == SDL_QUIT || (keystates[SDLK_LALT] && event.key.keysym.sym == SDLK_F4))
		{
			running = false;
			run_next = false;
		}
	}


	//måla lite fint
	paint();
	if(state == 5)
	  {
	    discard_button.paint(screen);
	  }
	else if(state == 4 && game_stage == 1)
	  {
	    play_button.paint(screen);
	    end_button.paint(screen);
	  }
	SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
	fps.regulateFPS();
	
	
}

void Game::paint()
{
	
	applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	  {
	    all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	  }
	
	if (game_stage != 0)
	  {
	    int i = 0;
	    
	    for(Player* p : players)
	      {	
		if(p -> isCurrentPlayer())
		  {
		    if(state != 0)
		      {
			p->setPos(0,0);
			p -> paint(screen);
		      }

		  }
		else
		  {
		    if(players.size() == 5 && state != 7)
		      {
			if(i - (int)self == -1 || i - (int)self == 4)
			  {
			    p-> setPos(30,300);
			    p -> paint(screen,30,300);    			  
			  }
			if(i - (int)self == -2 || i - (int)self == 3)
			  {
			    p -> setPos(175,30);
			    p -> paint(screen,175,30);
			  }
			if(i - (int)self == -3 || i - (int)self == 2)
			  {
			    p -> setPos(460,30);
			    p -> paint(screen,460,30);
			  }
			if(i - (int)self == -4 || i - (int)self == 1)
			  {
			    p -> setPos(605,300);
			    p -> paint(screen,605,300);
			  }
		      }
		    else if(players.size() == 5 && state == 7)
		      {
				target_player.at(0) -> setPos(30,200);
				target_player.at(0) ->paint(screen,30,200);
		      }
		  }
		++i;
	      }
	  }
	else
	  {
	    for(Player* p : players)
	      {
		if(p -> getRole() == 0)
		  p -> paint(screen,824,257);
	      }
	  }

	if(timer->checkStarted() == true)
	  {
	    timer->paint(screen);
	  }
	if(sett.getToolTips() == true && state != 0)
	  {
	    for(Player* pp : players)
	      {
		pp->showToolTip(screen);
	      }
	  }
}


int Game::getDistance(Player* source, Player* target)
{
	int distance;
	{ // fixar distance
		int self;
		int alive = 0;
		for(unsigned i = 0; i < players.size() ; ++i) //tmp 
		{
			if(players.at(i) -> getLife() > 0)
				++alive;
			if(players.at(i) == source)
				self = alive;
			if(players.at(i) == target)
				distance = alive;
		}
		//avstånd från en själv till target
		distance -= self;
		//om target är till vänster om en själv - invertera
		if ( distance < 0)
			distance = -distance;
		//om andra hållet är närmare - ta det hållet
		if (alive - distance < distance)
			distance = alive - distance;
		if(current_player -> equipment.off_horse != nullptr)
			--distance;
		if(target -> equipment.def_horse != nullptr)
			++distance;
	}
	return distance;
}

int Game::nextPlayer( int unique)
{
	int nP;
	if(unique != -1)
		nP = unique;
	else
		nP = self;
	do
	{
		nP = (nP+1)%players.size();
	}while(!(players.at(nP) -> isAlive()));
	
	return nP;
}

void Game::cleanPlayer(Player* what_player)
{
  timer->stop();
  Window* kill_window = new Window(150,100,500,500);

  GameCard* tmp_card;
  int x_offset = 20;
  int y_offset = 70;
  std::string tmp_name = what_player->getHeroName() + " was killed";
  Surface player_name = textToSurface(tmp_name, "Fonts/arial.ttf",20);
  tmp_card = what_player ->getJudgementCard();
  if(tmp_card != nullptr)
    {
      kill_window->addCard(tmp_card,x_offset,y_offset);
    }
  tmp_card = nullptr;
  x_offset += 50;
  while(what_player->getHand().size() > 0)
    {
      tmp_card = what_player->loseCard(0);
      kill_window->addCard(tmp_card,x_offset,y_offset);
      x_offset += 50;
      tmp_card = nullptr;
    }
  x_offset = 20;
  y_offset = 160;
  for(int i = 0 ; i < 4 ; ++i)
    {
      tmp_card = what_player -> loseEquipment(i);
      if(tmp_card != nullptr)
	kill_window->addCard(tmp_card, x_offset,y_offset);
    }

  kill_window->makeButton("Ok", 300,300, "continue");
  std::string command = "";
 
      has_window = true;
      while(has_window && running)
	{
	  while(SDL_PollEvent(&event))
	    {
	      command = kill_window->handleEvent(event);
	      exitCommand(event);
	    }
	  if(command == "continue")
	    {
	      has_window = false;
	    }

	  paint();
	  kill_window->paint(screen);
	  applySurface(200,330,player_name,screen);
	  SDL_Flip(screen.getImage());
	  fps.regulateFPS();
	}
      Object::Object* tmp_object = nullptr;
      while(kill_window->getSize() > 0)
	{
	  tmp_object = kill_window->remove(0);
	  if( dynamic_cast<GameCard*>(tmp_object) != nullptr)
	    {
	      discard_pile -> pushBottom(dynamic_cast<GameCard*>(tmp_object));
	    }
	  else if(tmp_object != nullptr)
	  {
		  delete tmp_object;
	  }
	}
      delete kill_window;
      timer->reset(sett.getTimerTime(), timer->getCommand());
}

void Game::exitCommand(SDL_Event& event)
{
  if( event.type == SDL_QUIT || (keystates[SDLK_LALT] && event.key.keysym.sym == SDLK_F4))
    {
      running = false;
      run_next = false;
    }
}

bool Game::useCard(const std::string& cardID, const std::string& description, Player* player)
{
	if(!running)
		return false;
	std::string old_timer_command = timer -> getCommand();
	timer->reset(sett.getTimerTime(), "skip");
	bool occured = false;
	std::string command;
	Window options(175,125,450,400);
	options.makeTextbox(30,30,340,80,25);
	options.setText(0,description);
	if(cardID != "discard")
		options.makeButton("Use "+cardID,15,330,"use");
	else
		options.makeButton("Discard",15,330,"use");
		
	options.makeButton("Skip",215,330,"skip");
	options.makeButton("Show hand",115,230,"show_hand");
	bool has_window = true;
	std::vector<GameCard*> hand = player->getHand();
	GameCard* card;
	bool show_hand = false;
	
	Button play_button("Play", 800, 575, "play","Images/Gui/smallButton.png",20);
	Button skip_button("Skip", 800, 630, "skip","Images/Gui/smallButton.png",20);
	Textbox information(250,270,400,120,"Fonts/LHANDW.TTF",20);
	information.setText(description);
	GameCard* selected_card = nullptr;
	while(has_window && running)
	{
		if(!show_hand)
		{
			command = timer->time_ran_out();
			while(SDL_PollEvent( &event))
			{
				exitCommand(event);
				if(command == "")
					command = options.handleEvent(event);
			}
		
			if(command == "skip")
			{
				occured = false;
				has_window = false;
			}
			else if(command == "use")
			{
				if(cardID == "discard")
				{
					unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
					std::cout << seed;
					card = player -> playCard(seed%hand.size());
					occured = true;
				}
				else
				{
					for(unsigned i = 0; i < hand.size(); ++i)
					{
						if(hand.at(i) -> getAbility() == cardID)
						{
							card = player -> playCard(i);
							occured = true;
							break;
						}
					}
				}
	      
				if(card != nullptr)
				{
					discard_pile -> pushBottom(card);
				}
				else
					occured = false;
	      
				has_window = false;
	      
			}
			else if(command == "show_hand")
			{
				timer->reset(sett.getTimerTime(), "skip");
				show_hand = true;
			}
		}
		else
		{
			command = timer->time_ran_out();
			while(SDL_PollEvent( &event))
			{
				exitCommand(event);
				if(command == "")
					command = play_button.handleEvent(event);
				if(command == "")
					command = skip_button.handleEvent(event);
				if(command == "" && event.type == SDL_MOUSEBUTTONUP)
					selected_card = player -> handleHand(event);
			}
		
			if(command == "play")
			{
				if(selected_card != nullptr && selected_card -> getAbility() == cardID)
				{
					std::vector<GameCard*> hand = player ->getHand();
					for(unsigned i = 0; i < hand.size() ; ++i)
					{
						if(hand.at(i) == selected_card)
						{
							discard_pile ->pushBottom(player -> playCard(i));
						}
					}
					occured = true;
					has_window = false;
				}
				
			}
			if(command == "skip")
			{
				occured = false;
				has_window = false;
			}
		}
		//LiTHe paint
		applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
		for(unsigned i = 0; i < all_objects.size() ; ++i)
		{
			all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
		}
		
		if(timer->checkStarted() == true)
		{
			timer->paint(screen);
		}
		
		if(show_hand)
		{
			player->paint(screen);
			information.paint(screen);
			play_button.paint(screen);
			skip_button.paint(screen);
		}
		else
		{
			options.paint(screen);
			player->setPos(600,240);
			player->paint(screen,600,240);
		}
		
		SDL_Flip(screen.getImage());
		fps.regulateFPS();
	}
	
	timer->reset(sett.getTimerTime(), old_timer_command);
	return occured;
}
	
	
void Game::modifyLife(Player* what_player, int value)
{
	what_player -> modifyLife(value);
	bool saved = true;
	while(what_player -> getLife() <= 0 && saved)
	{
		saved = false;
		int nP = self;
		do
		{
			if(useCard("heal",what_player->getName()+" is dying, would you like to save him by using peach?", players.at(nP)))
				saved = true;
			nP = nextPlayer(nP);
		}while(nP != self && !saved);
	}
	if(what_player -> getLife() <= 0)
	{
		what_player -> kill();
		if(what_player -> getRole() == 3 && what_player != current_player) //Killing Rebel reward!
		{
			GameCard* card;
			for(int i = 0; i < 3 ; ++i)
			{
				if(card_deck -> empty())
				{
					std::swap(card_deck,discard_pile);
					card_deck -> shuffle();
				}
				if(card_deck -> empty())
					throw SGS_error("card deck and discard deck totally empty!");
				else
				{
					card = dynamic_cast<GameCard*>(card_deck -> drawCard());
					players.at(self) -> recieveCard(card);
				}
			}
		}
		
		if(what_player -> getRole() == 1 && current_player -> getRole() == 0) //Emperor killing Loyal punishment!
		{
			cleanPlayer(current_player);
		}
		
		
		cleanPlayer(what_player);
		int winner = ruleWinCondition();
		if(winner != 0)
		{
			end(winner);
		}
		if(what_player == current_player)
			state = 5;		
	}
}

	
bool Game::shieldBlock(std::string type, int p_index)
{
	std::cerr<< "Shieldblock for: " << type << std::endl;
	std::string old_timer_cmd = timer->getCommand();
	timer->reset(sett.getTimerTime(),"ok");
	
	bool blocked = false;
	Window* block_window = new Window(130,200,400,400);
	block_window->makeButton("Ok", 120,350,"ok");
	block_window->makeTextbox(50,50,300,70);
	has_window = false;	
	std::string command = "";
	GameCard* judge_card;
	bool unblockable = false;
	if(type == "arrows")
	{
		std::cerr << "TYPE IS ARROWS" << std::endl;
		if(players.at(p_index)->equipment.shield != nullptr)
		{
			if(players.at(p_index)->equipment.shield->getAbility() == "shield0")
			{
				std::cerr << "Judgement shield time" << std::endl;
				has_window = true;
				judge_card = dynamic_cast<GameCard*>(card_deck -> drawCard());
				block_window->addCard(judge_card,50,140);
				if( judge_card -> getSuit() == hearts || judge_card -> getSuit() == diamonds)
				{
					blocked = true;
					block_window->setText(1,"Red judgement card, arrows dodged with shield");
				}
				else
				{
					block_window->setText(1,"Black judgement card, arrows not dodged");
				}
			}
		}
	}
	else
	{
		if(current_player->equipment.weapon != nullptr)
		{
			if(current_player->equipment.weapon->getAbility() == "weapon0")
			{
				unblockable = true;
			}
		}
		
		if(target_player.at(0)->equipment.shield != nullptr && unblockable == false)
			{
				if(target_player.at(0)->equipment.shield->getAbility() == "shield1")
					{	
						if(selected_card->getSuit() == spades || selected_card->getSuit()  == clubs)
						{
							blocked = true;
							block_window->setText(1,"Black attack blocked");
							has_window = true;
						}
					}
					if(target_player.at(0)->equipment.shield->getAbility() == "shield0")
					{
						std::cerr << "Judgement shield time" << std::endl;
						has_window = true;
						judge_card = dynamic_cast<GameCard*>(card_deck -> drawCard());
						block_window->addCard(judge_card,50,140);
						if( judge_card -> getSuit() == hearts || judge_card -> getSuit() == diamonds)
						{
							blocked = true;
							block_window->setText(1,"Red judgement card, attack blocked by shield");
						}
						else
						{
								block_window->setText(1,"Black judgement card, attack not blocked");
						}
					}
			}
	}
			while(has_window)
			{
				command = timer->time_ran_out();
					while(SDL_PollEvent(&event))
						{
								if(command == "")
								{									
									command = block_window->handleEvent(event);
								}
						}						
				if(command == "ok")
				{
					has_window = false;
				}					
				
				paint();
				block_window->paint(screen);
				SDL_Flip(screen.getImage());
				fps.regulateFPS();
			}
			 Object::Object* tmp_object = nullptr;
			while(block_window->getSize() > 0)
			{
				tmp_object = block_window->remove(0);
				if( dynamic_cast<GameCard*>(tmp_object) != nullptr)
				{
					discard_pile -> pushBottom(dynamic_cast<GameCard*>(tmp_object));
				}
				else if(tmp_object != nullptr)
				{
					delete tmp_object;
				}
			}
			delete block_window;
				
		
	timer->reset(sett.getTimerTime(), old_timer_cmd);
	return blocked;
}
#include "game_commands.cpp"
#include "card_commands.cpp"
#include "rulebook.cpp"


