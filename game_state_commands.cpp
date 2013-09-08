
void GameState::run_command(const std::string& what_command,const int& current)
{
	if(what_command == "exit")
	{
		running = false;
		return;
	}
	if(what_command == "make_new_game")
	{
		dynamic_cast<text_box*>(all_objects.at(0))->set_text("You cannot make a new  game yet!");
		for(int a = 0 ; a <= current ; ++a)
		{
			all_objects.at(a)->print(screen);
		}
		return;
	}
	if(what_command == "options")
	{
		dynamic_cast<text_box*>(all_objects.at(0))->set_text("You cannot change options yet!");
		for(int a = 0 ; a <= current ; ++a)
		{
			all_objects.at(a)->print(screen);
		}
		return;
	}
		if(what_command == "delete_button")
	{
		delete all_objects.at(all_objects.size()-1);
		all_objects.erase(all_objects.begin()+all_objects.size()-1);
		return;
	}
}