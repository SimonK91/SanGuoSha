//using namespace object;
#include <stdexcept>
void Menu::run_command(const std::string& what_command)
{
	if(what_command == "")
		return;
		
	
	if(what_command == "exit")
	{
		running = false;
		return;
	}
	if(what_command == "make_new_game")
	{
		Window* gameOptions = new Window(160,50,500,250);
		gameOptions->makeButton("Network",30,70,"play_on_network");
		gameOptions->makeButton("Hotseat",260,70,"play_on_hotseat");
		gameOptions->makeButton("Back",140,190,"close_window");
		gameOptions->makeTextbox(30,15,440,40, 20);
		gameOptions->setText(3,"which playing mode do you want?");
		add_window(gameOptions);
		has_window = true;
		// dynamic_cast<Textbox*>(all_objects.at(0))->setText("You cannot make a new game yet!");
	}
	
	if(what_command == "play_on_network")
	{
		throw SGS_error("Command: "+ what_command +" not implemented yet");
	}
	
	if(what_command == "play_on_hotseat")
	{
		//remove chois window
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;

		m.stop();
		Game game(screen);
		game.load_background("Images/Gui/background.png");
		
		//skapa spelets layout
		//game.make_button("exit", 350, 50, "close");
		Window* hand = new Window(155,545,664,223);
		Window* profile = new Window(864,545,160,223);
		Window* equipment = new Window(0,545,154,223);
		Window* chat = new Window(800,0,224,500);
		chat->makeTextbox(5,100,215,395);
		//game.set_text(0,"chat chat chat chat");
		chat->makeButton("Exit",10,10,"close");
		game.add_window(hand);
		game.add_window(profile);
		game.add_window(equipment);
		game.add_window(chat);
		if(!game.setup())
		  {
		    running = false;
		  }
		//game.make_button("end turn", 800, 575, "end_turn");
		//game.make_button("play card", 800, 630, "play_card");
		//bara preliminärt!
		game.run();
		if(!game.exit())
			throw std::runtime_error("oups!! game exit failed!!");
		
		else{ std::cout << "game.exit() okay!" << std::endl;}
		// game.run();
		m.play();	//fungerar inte som den ska :( 
		fps.start();
		// dynamic_cast<Textbox*>(all_objects.at(0))->setText("You cannot make a new game yet!");
	}
	if(what_command == "options")
	{
		Window* options = new Window(160,50,500,450);
		options->makeButton("Fullscreen",30,20,"toggle_fullscreen");
		options->makeButton("Back",270,390,"close_window");
		options->makeTextbox(300,20,150,30);
		options->setText(2,"Music volume: " + I2S(m.getVolume()));
		options->makeSlider(250,60,"set_volume",m.getVolume());
		add_window(options);
		has_window = true;
	}
	if(what_command == "close_window")
	{
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
	}
	if(what_command.substr(0,10) == "set_volume")
	{
		//hitta grejer3
		int volume = S2I(what_command.substr(11,what_command.size()-11));
		m.setVolume(volume);
		//settings.at(1).second = I2S(volume);
		dynamic_cast<Window*>(all_objects.back())->setText(2,"Music volume: " +  I2S(m.getVolume()));
	}
	if(what_command == "toggle_fullscreen")
	{
		if(!fullscreen)
		{
			screen = SDL_SetVideoMode(1024,768,32, screen->flags+SDL_FULLSCREEN);
			fullscreen = true;
			//settings.at(2).second = "on";
		}
		else
		{
			screen = SDL_SetVideoMode(1024,768,32, screen->flags-SDL_FULLSCREEN);
			fullscreen = false;
			//settings.at(2).second = "off";
		}
	}


	if(what_command == "set_settings")
	  {
	    
	    //toggle sounds not yet implementet

	    //set volume
		if(settings.size() > 2)
		{
	     int volume = S2I(settings.at(1).second);
	    m.setVolume(volume);
	    //fullscreen on/off
	    if(settings.at(2).second == "on")
	      {
		screen = SDL_SetVideoMode(800,600,32, screen->flags+SDL_FULLSCREEN);
		fullscreen = true;
	      }
	    else
	      {
		//screen = SDL_SetVideoMode(800,600,32, screen->flags-SDL_FULLSCREEN);
		fullscreen = false;
	      }
		}
		else
		{
			m.setVolume(67);
			fullscreen = false;
		}
	  }
	return;
}
