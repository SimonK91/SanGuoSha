#include "SGS.h"
#include <chrono>
#include <algorithm>

using namespace Object;


bool Game::setup()
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
			std::cout << "Emperor-cards drawn" << std::endl;	
			
			hero_deck->shuffle();
			std::cout << "hero_deck shuffled" << std::endl;
			
			Card* hero4 = hero_deck->drawCard();
			Card* hero5 = hero_deck->drawCard();
			std::cout << "two more cards drawn" << std::endl;
			
			if(emperor == self)
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
			return run_next;

			
		// std::cerr << "painting" << std::endl;
		UI();
		// std::cerr << "post painting" << std::endl;
	}
	
	return run_next;
}

void Game::run()
{
	game_stage = 1;
//game
	//clean up!
	while(!players.empty())
	{
		delete players.back();
		players.pop_back();
	}
	//blanda leken :D
	card_deck -> shuffle();
	
	GameCard* card = nullptr;
	//simulerade spelare:
	Player* player = new Player();
	player -> setRole(0); //emparor
	player -> setHero(new HeroCard("CaoCao.png", "4 blue 1 ability"));
	players.push_back(player);
	
	player = new Player();
	player -> setRole(1); 
	player -> setHero(new HeroCard("DiaoChan.png", "3 gray 0 ability"));
	players.push_back(player);
	
	player = new Player();
	player -> setRole(2);
	player -> setHero(new HeroCard("DaQiao.png", "3 green 0 ability"));
	players.push_back(player);
	
	player = new Player();
	player -> setRole(2);
	player -> setHero(new HeroCard("ElderZhuge.png", "3 red 1 ability"));
	players.push_back(player);	
	player = nullptr;
	
	player = new Player();
	player -> setRole(3);
	player -> setHero(new HeroCard("SiMaYi.png", "3 blue 2 ability"));
	players.push_back(player);	
	player = nullptr;
	
	running = true;
	card_deck -> pushTop(new GameCard(6,spades,"blue_steel_blade.png","equip_weapon_blue_steel_blade 5 0")); //ability id, target type, target range
	card_deck -> pushTop(new GameCard(2,spades,"double_gender_sword.png","equip_weapon_double_gender_sword_equip 5 0")); //ability id, target type, target range
	card_deck ->pushTop(new GameCard(13,hearts,"zhua_huang.png","equip_def_horse 5 0"));
	card_deck ->pushTop(new GameCard(13,hearts,"zhua_huang.png","equip_def_horse 5 0"));
	card_deck ->pushTop(new GameCard(13,spades,"da_wan.png","equip_off_horse 5 0"));
	card_deck ->pushTop(new GameCard(2,clubs,"ren_wang_shield.png","equip_shield_ren_wang_shield_equip 5 0"));
	while(running)
	{
	 
	  std::string cmp = timer->time_ran_out();
	  if(cmp != "")
	   {
	     std::cout << "Kor kommandot: " << cmp << std::endl;
	     run_command(cmp);
	     //timer->stop();
	   }
	   // std::cout << timer->time_ran_out() << std::endl;
	//phase 1)
	//start of turn
	//special hero abilities trigger here
		// std::cout << "the state: " << state << std::endl;
		if(state == 1)
		{
		  //timer
		  timer->start(5);

		  players.at(self) -> setCurrentPlayer(true);
		  current_player = players.at(self);
		  for(auto p : players)
		    {
		      p->setSelected(false);
		    }
		  state = 2;
		}
	//phase 2
	//judgement phase
	//pending cards activate in stacked order
	//negate can remove pending card
	//else judge
		else if(state == 2)
		{
			state = 3;
		}
	//phase 3
	//drawing phase
	//special hero abilities trigger here
	//draw 2 cards
		else if(state == 3)
		{
			//check if card_deck is empty
			if(card_deck -> empty())
				std::swap(card_deck,discard_pile);
				
			//draw 2 cards
			card = dynamic_cast<GameCard*>(card_deck -> drawCard());
			players.at(self) -> recieveCard(card);
			
			if(card_deck -> empty())
				std::swap(card_deck,discard_pile);
						
			card = dynamic_cast<GameCard*>(card_deck -> drawCard());
			players.at(self) -> recieveCard(card);
			
				/*
				<insert hero abilitys here>
				*/
			state = 4;
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
			if(players.at(self) -> getCurrentHP() >= players.at(self) -> getHandSize())
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
			self = (self + 1) % players.size();
			state = 1;
			target_player = nullptr;

			if(timer->checkStarted() == true)
			  {
			    timer->stop();
			    timer->setCommand("end_turn");
			  }
		}
	//phase 7
        //other player phase
        //other heroes responds to your played cards
		else if(state == 7)
		  {
		    
		    
		  }


		UI(); //call the UI for repaint
	}//player loop
	
//if a player dies, check for winning conditions
//if an equipment is added/removed, update player stats
//if a card is active, check rule-book for targets
//if a valid target is selected, activate button "play card"
//if a player is targetted by an effect, check possible plays.
//if a tool-card is played, check every player for negate card.
}

bool Game::end()
{
//show score-table
//keep chat open
//make exit button
	return true; //:D
}

bool Game::exit()
{
	//clean up everything!!
	try
	{
	// writeSettings(settings);
		while(!all_objects.empty())
		{
			delete all_objects.back();
			all_objects.pop_back();
		}
		while(!players.empty())
		{
			delete players.back();
			players.pop_back();
		}
		delete card_deck;
		delete hero_deck;
		delete discard_pile;
	}
	catch(...)
	{
		return false;
	}

	return true;
}

void Game::UI()
{
	Uint8 *keystates = SDL_GetKeyState(nullptr);
	std::string command;
	static Button discard_button("Discard", 800, 685, "discard_card","Images/Gui/smallButton.png",20);
	static Button play_button("Play", 800, 575, "play_card", "Images/Gui/smallButton.png",20);
	static Button end_button("End", 800, 630, "end_turn", "Images/Gui/smallButton.png",20);

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

		std::string button_command;
		if(state == 5)
		  {
			button_command = discard_button.handleEvent(event);
			run_command(button_command);
		  }
		else
		  {
		    button_command = play_button.handleEvent(event);
		    run_command(button_command);
		    if(button_command == "")
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
		//kolla spelare och nuvarande handen
		for(Player* q : players)
		  {
		    q -> handleEvent(event);
		  }

		if(event.type == SDL_MOUSEBUTTONUP && !has_window && game_stage == 1)
		{
			//om inte, gör detta!
			if(button_command == "")
			{
				bool player_pressed = false;
				//rensa selection
				for(Player* p : players)
				{
					p->setSelected(false);
				}
				target_player = nullptr;
			
				//fixa med players o deras event!
				for(Player* p : players)
				{
					if(p -> handleEvent(event))
					{
						target_player = p;
						p->setSelected(true);
						player_pressed = true;
						break;
					}
				}
				if(!player_pressed && button_command == "")
				{
					if(current_player != nullptr)
						current_player -> handleHand(event);
					current_player -> fixCardPosition();
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
	else
	  {
	    play_button.paint(screen);
	    end_button.paint(screen);
	  }
	SDL_Flip(screen.getImage());                   // Skriv ut bilden pÃ¥ skÃ¤rmen
	fps.regulateFPS();
}

//från menyn
/*
game.setup();
game.run();

run()
{
	//fixa alla faser o grejer!
	
	manageEvents
	
	paint();
}

paint()
{
	//rita ut alla objekt + kort
	
	//eller så får den ha faser!
}

UI()
{
	manageEvents;
	paint;
}

*/
void Game::paint()
{
std::cerr << "player line 466" << std::endl;
	
	applySurface(0,0,background,screen); //skriv ut bakgrunden att ha som en bas
	std::cerr << "player line 469" << std::endl;
	
	for(unsigned i = 0; i < all_objects.size() ; ++i)
	{
		all_objects.at(i)->paint(screen); // fÃ¶r varje objekt (oavsett aktivt eller inte), skriv ut det pÃ¥ skÃ¤rmen
	}
	std::cerr << "line 475" << std::endl;

	int player_paint_offset_x = 200;
	int player_paint_offset_y = 25;
	unsigned others = 0;
	for(unsigned i = 0; i < players.size(); ++i)
	  {
	    if(players.at(i) -> isCurrentPlayer())
	      {
		players.at(i) -> paint(screen);
	      }
	    else
	      {
		players.at(i)->setPos(player_paint_offset_x, player_paint_offset_y);
		players.at(i) -> paint(screen);
		others++;
		if(others == 1)
		  {
		     player_paint_offset_x = 400;
		  }
		else if(others == 2)
		  {
		    player_paint_offset_x = 75;
		    player_paint_offset_y = 270;
		  }
		else if(others == 3)
		  {
		    player_paint_offset_x = 525;
		    player_paint_offset_y = 270;
		  }
	      }
	  }
	if(timer->checkStarted() == true)
	  {
	    timer->paint(screen);
	  }
}


#include "game_commands.cpp"
#include "card_commands.cpp"


