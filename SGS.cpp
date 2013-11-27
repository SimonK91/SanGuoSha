#include "SGS.h"

using namespace Object;

//Destruktor
SGS::~SGS()
{
	while(!all_objects.empty())
	{
		delete all_objects.back();
		all_objects.pop_back();
	}	
} //destruering sker i slutet av run!


//Mainfunktionen i GameState




//för att skapa alla objekttyper
bool SGS::make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command,
							const std::string& image, const unsigned& size)
{
	Button* temp = new Button(name, x_pos, y_pos, command, image, size);
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}
bool SGS::make_slider(const int& x_pos, const int& y_pos, const std::string& command)
{
	Slider* temp = new Slider(x_pos, y_pos, command,m.getVolume());
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}

bool SGS::make_textbox(const int& x, const int& y, const int& w , const int& h
							,const SDL_Color &col, const std::string& font, const unsigned& size)
{
	Textbox* temp = new Textbox(x,y,w,h,col,font,size);
	
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	//all_objects.pop_back();
	return true;
	
}
bool SGS::add_window(Object::Window* your_window)
{
	if(your_window == nullptr)
		return false;
	all_objects.push_back(your_window);
	return true;
}

bool SGS::make_checkbox(int x, int y, const std::string& command, bool checked)
{
	Checkbox* tmp = new Checkbox(x,y,command,checked);
	if(tmp == nullptr)
		return false;
	all_objects.push_back(tmp);
	return true;
}
void SGS::set_text(const int& where, const std::string& what_text)
  {
    if(dynamic_cast<Textbox*>(all_objects.at(where)) != nullptr)
      dynamic_cast<Textbox*>(all_objects.at(where))->setText(what_text);
  }

