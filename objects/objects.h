#ifndef OBJECTS_H
#define OBJECTS_H

#include "../functions.h"
#include "pointer_arrow.h"
#include <string>
#include <vector>

namespace object
{
class object
{
private:

protected:
	SDL_Rect box;
	
public:
	virtual bool loaded() = 0;
 object(){}
virtual ~object(){}

	virtual void print(SDL_Surface*) = 0;
};

class dead_object : public object
{
private:

public:
	dead_object(){}
	virtual ~dead_object(){}
};

class active_object : public object
{
private:

protected:
	int active;

public:
	virtual std::string handle_event(const SDL_Event&, const pointer_arrow&) = 0;
	active_object(){}
	virtual ~active_object(){}
 };


}//slut på namnrymden
#endif