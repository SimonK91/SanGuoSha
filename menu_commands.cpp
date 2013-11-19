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
		// m.pause();
		m.stop();
		Game game(screen);
		game.load_background("Images/Gui/background.png");
		game.make_button("exit", 350, 50, "exit");
		game.setup();
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
		options->makeTextbox(("Music volume: " + I2S(m.getVolume())),300,20,150,30);
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
			screen = SDL_SetVideoMode(800,600,32, screen->flags+SDL_FULLSCREEN);
			fullscreen = true;
			//settings.at(2).second = "on";
		}
		else
		{
			screen = SDL_SetVideoMode(800,600,32, screen->flags-SDL_FULLSCREEN);
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
