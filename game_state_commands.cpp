void GameState::run_command(const std::string& what_command)
{
	if(what_command == "exit")
	{
		running = false;
		return;
	}
	if(what_command == "make_new_game")
	{
		make_button("Exit",300,500,"exit");
		return;
	}
	if(what_command == "test_leaks")
	{
		make_button("Exit",300,500,"exit");
		delete all_objects.at(all_objects.size()-1);
		all_objects.erase(all_objects.begin()+all_objects.size()-1);
		return;
	}
		if(what_command == "delete_button")
	{
		delete all_objects.at(all_objects.size()-1);
		all_objects.erase(all_objects.begin()+all_objects.size()-1);
		return;
	}
}