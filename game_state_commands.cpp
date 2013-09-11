using namespace object;
void GameState::run_command(const std::string& what_command,unsigned& current)
{
	if(what_command == "exit")
	{
		running = false;
		return;
	}
	if(what_command == "make_new_game")
	{
		m.stop();
		dynamic_cast<text_box*>(all_objects.at(0))->set_text("You cannot make a new game yet!");
	}
	if(what_command == "options")
	{
		window* options = new window(160,50,500,450);
		options->make_button("Fullscreen",30,20,"toggle_fullscreen");
		options->make_button("Back",270,390,"close_window");
		options->make_text_box(("Music volume: " + I2S(m.getVolume())),300,20,150,30);
		options->make_slider(250,60,"set_volume",m.getVolume());
		add_window(options);
		has_window = true;
	}
	if(what_command == "close_window")
	{
		delete all_objects.at(current);
		all_objects.erase(all_objects.begin()+current,all_objects.begin()+current+1);
		has_window = false;
		--current;
	}
	if(what_command.substr(0,10) == "set_volume")
	{
		//hitta grejer3
		int volume = S2I(what_command.substr(11,what_command.size()-11));
		m.setVolume(volume);
		dynamic_cast<window*>(all_objects.at(current))->set_text(2,"Music volume: " + I2S(volume));
	}
	if(what_command == "toggle_fullscreen")
	{
		if(!fullscreen)
		{
			screen = SDL_SetVideoMode(800,600,32, screen->flags+SDL_FULLSCREEN);
			fullscreen = true;
		}
		else
		{
			screen = SDL_SetVideoMode(800,600,32, screen->flags-SDL_FULLSCREEN);
			fullscreen = false;
		}
	}
	for(int a = 0 ; a <= current ; ++a)
		{
			all_objects.at(a)->print(screen);
		}
	return;
}
