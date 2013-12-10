//using namespace object;
#include <stdexcept>
void Menu::run_command(const std::string& what_command)
{
	if(what_command == "")
		return;
		
	
	if(what_command == "exit")
	{
		running = false;
		sett.writeSettings();
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
	  int tmp = 0;
	  std::cout << "play on hotseat" << std::endl;
		//remove chois window
		delete all_objects.back();
		all_objects.pop_back();
		has_window = false;
		std::cerr << "tmp: " << tmp++ << std::endl;
		m.stop();
		std::cerr << "tmp: " << tmp++ << std::endl;
		Game game(screen, sett);
		std::cerr << "tmp: " << tmp++ << std::endl;
		game.load_background("Images/Gui/background.png");
		std::cerr << "tmp: " << tmp++ << std::endl;
		
		//skapa spelets layout
		//game.make_button("exit", 350, 50, "close");
		std::cerr << "tmp: " << tmp++ << std::endl;
		Window* hand = new Window(155,545,664,223);
		std::cerr << "tmp: " << tmp++ << std::endl;
		Window* profile = new Window(864,545,160,223);
		std::cerr << "tmp: " << tmp++ << std::endl;
		Window* equipment = new Window(0,545,154,223);
		std::cerr << "tmp: " << tmp++ << std::endl;
		Window* chat = new Window(800,0,224,500);
		std::cerr << "tmp: " << tmp++ << std::endl;
		chat->makeTextbox(5,100,215,395);
		std::cerr << "tmp: " << tmp++ << std::endl;
		//game.set_text(0,"chat chat chat chat");
		std::cerr << "tmp: " << tmp++ << std::endl;
		chat->makeButton("Exit",10,10,"close");
		std::cerr << "tmp: " << tmp++ << std::endl;
		game.add_window(hand);
		std::cout << "tmp: " << tmp++ << std::endl;
		game.add_window(profile);
		std::cout << "tmp: " << tmp++ << std::endl;
		game.add_window(equipment);
		std::cout << "tmp: " << tmp++ << std::endl;
		game.add_window(chat);
		std::cout << "tmp: " << tmp++ << std::endl;
		game.setupHotseat();
		std::cout << "tmp: " << tmp++ << std::endl;
		if(game.runNext())
		{
			game.runHotseat();
		}
	
		if(!game.runNext())
			running = false;
		//game.make_button("end turn", 800, 575, "end_turn");
		//game.make_button("play card", 800, 630, "play_card");
		//bara preliminärt!
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
		Window* options = new Window(250,50,500,450);
		options->makeButton("Fullscreen",30,60,"toggle_fullscreen");
		options->makeButton("Back",380,390,"close_window", "Images/Gui/mediumButton.png");
		options->makeTextbox(290,25,150,30);
		options->setText(2,"Music volume: " + I2S(m.getVolume()));
		options->makeSlider(250,60,"set_volume",m.getVolume());
		std::cout << "make textbbox" << std::endl;
		options->makeTextbox(290,125,150,30);
		std::cout << "settext" << std::endl;
		options->setText(4,"Effects volume: " + I2S(m.getEffectVolume()));
		std::cout << "makeslider" << std::endl;
		options->makeSlider(250,160,"set_effects_volume",m.getEffectVolume());
		std::cout << "add windows" << std::endl;
		options->makeTextbox(30,160,120,30);
	
		std::string tmp_on_off = "";
		if(sett.getToolTips())
		  tmp_on_off = "On";
		else
		  tmp_on_off = "Off";
		options->setText(6,"Tool tips: " + tmp_on_off);
		options->makeCheckbox(50, 200, "tool_tips", sett.getToolTips());
		
		options->makeTextbox(30, 250, 200,30);
		options->setText(8,"Timer length: " + I2S(sett.getTimerTime()));
		options->makeButton("5",30,300, "timer5","Images/Gui/timerButton.png", 15);
		options->makeButton("10",60,300, "timer10","Images/Gui/timerButton.png", 15);
		options->makeButton("15",90,300, "timer15","Images/Gui/timerButton.png", 15);
		options->makeButton("20",120,300, "timer20","Images/Gui/timerButton.png", 15);

		add_window(options);
		has_window = true;
	}
	if(what_command.substr(0,5) == "timer")
	  {
	    sett.setTimerTime(S2I( what_command.substr(5,what_command.size())));
	    dynamic_cast<Window*>(all_objects.back())->setText(8, "Timer length: " + I2S(sett.getTimerTime()));
			      
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
		std::cout << "MUSIC VOLYM: " << volume << std::endl;
		//settings.at(1).second = I2S(volume);
		sett.setMusicVolume(volume);
		dynamic_cast<Window*>(all_objects.back())->setText(2,"Music volume: " +  I2S(m.getVolume()));
	}
	if(what_command.substr(0,18) == "set_effects_volume")
	  {
	    int volume = S2I(what_command.substr(19,what_command.size()-11));
	    std::cout << "EFFECT VOLYM: " << volume << std::endl;
	    sett.setEffectVolume(volume);
	    m.setEffectVolume(volume);
	    dynamic_cast<Window*>(all_objects.back())->setText(4,"Effects volume: " +  I2S(m.getEffectVolume()));
	  }
	if(what_command == "toggle_fullscreen")
	{
		if(!fullscreen)
		{
			screen = SDL_SetVideoMode(1024,768,32, screen->flags+SDL_FULLSCREEN);
			fullscreen = true;
			sett.setFullscreen(true);
		}
		else
		{
			screen = SDL_SetVideoMode(1024,768,32, screen->flags-SDL_FULLSCREEN);
			fullscreen = false;
			sett.setFullscreen(false);
		}
	}

	if(what_command.substr(0,9) == "tool_tips")
	  {
	    
	    if(what_command.substr(9,what_command.size()) == "true")
	      {
		std::cerr << "turning tooltips: ON" << std::endl;
		sett.setToolTips(true);
	      }
	    else
	      {
		std::cerr << "turning tooltips: OFF" << std::endl;
		sett.setToolTips(false);
	      }
	    std::string tmp_on_off = "";
	    if(sett.getToolTips())
	      tmp_on_off = "On";
	    else
	      tmp_on_off = "Off";
	    dynamic_cast<Window*>(all_objects.back())->setText(6,"Tool tips: " + tmp_on_off);
	  }
	if(what_command == "set_settings")
	  {

	    m.setVolume(sett.getMusicVolume());
	    m.setEffectVolume(sett.getEffectVolume());
	    fullscreen = sett.getFullscreen();
	   
	    //toggle sounds not yet implementet

	    //set volume
		if(settings.size() > 2)
		{
		  // int volume = S2I(settings.at(1).second);
		  //m.setVolume(volume);
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
