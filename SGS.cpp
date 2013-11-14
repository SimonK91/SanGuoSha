#include "SGS.h"

using namespace object;

//Destruktor
SGS::~SGS(){} //destruering sker i slutet av run!


//Mainfunktionen i GameState




//för att skapa alla objekttyper
bool SGS::make_button(const std::string& name, const int& x_pos, const int& y_pos, const std::string& command,
							const std::string& image, const unsigned& size)
{
	button* temp = new button(name, x_pos, y_pos, command, image, size);
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}
bool SGS::make_slider(const int& x_pos, const int& y_pos, const std::string& command)
{
	slider* temp = new slider(x_pos, y_pos, command,m.getVolume());
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	return true;
}

bool SGS::make_textbox(const std::string& text, const int& x, const int& y, const int& w , const int& h
							,const SDL_Color &col, const std::string& font, const unsigned& size)
{
	text_box* temp = new text_box(text,x,y,w,h,col,font,size);
	
	if (temp == nullptr)
		return false;
	all_objects.push_back(temp);
	//all_objects.pop_back();
	return true;
	
}
bool SGS::add_window(object::window* your_window)
{
	if(your_window == nullptr)
		return false;
	all_objects.push_back(your_window);
	return true;
}

bool SGS::make_checkbox(int x, int y, const std::string& command, bool checked)
{
	CheckBox* tmp = new CheckBox(x,y,command,checked);
	if(tmp == nullptr)
		return false;
	all_objects.push_back(tmp);
	return true;
}

