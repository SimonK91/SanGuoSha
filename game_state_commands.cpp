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
		dynamic_cast<text_box*>(all_objects.at(0))->set_text("You cannot make a new game yet!");
	}
	if(what_command == "options")
	{
		window* options = new window(160,50,500,450);
		options->makeButton("Fullscreen",30,20,"toggle_fullscreen");
		options->makeButton("Back",270,390,"close_window");
		options->makeTextBox("Modify sound",300,20,150,30);
		options->makeSlider(250,60,"set_sound");
		add_window(options);
		has_window = true;
		dynamic_cast<text_box*>(all_objects.at(0))->set_text("You cannot change options yet!");
	}
	if(what_command == "close_window")
	{
		delete all_objects.at(current);
		all_objects.erase(all_objects.begin()+current,all_objects.begin()+current+1);
		has_window = false;
		--current;
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