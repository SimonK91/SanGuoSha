#include "objects.h"

ClickBox : public active_object
{
private:
	bool inside(SDL_Event event);

public:
	ClickBox(int x, int y, int w, int h, std::string command)
	~ClickBox() = default;
	std::string handleEvent(const SDL_Event& event);
	void paint(){}

}