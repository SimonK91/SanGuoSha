#ifndef OBJECTS_H
#define OBJECTS_H

#include "../functions.h"
#include "pointer_arrow.h"
#include <string>
#include <vector>

namespace object
{

//bashierarkin - abstrakt som bara den
class object
{
private:

protected:
	//konstruktorer och operatorer som ej används!
	object() = default;
	object(const object&) = delete;
	object(object&&) = delete;
	object& operator=(const object&) = delete;
	object& operator=(object&&) = delete;
	
	SDL_Rect box;
	SDL_Rect clip;
public:
	virtual ~object(){}
	virtual void print(SDL_Surface*) = 0;
};

//alla objekt som inte har någon funktion i sig
class dead_object : public object
{
private:

protected:

public:
	virtual ~dead_object() = default;
};

//alla objekt som har en funktion med något kommando.
class active_object : public object
{
private:

protected:
	int active;
	std::string command;

public:
	active_object() : object() , active(0), command(""){}
	
	int isActivated(){ return active; }
	virtual std::string handle_event(const SDL_Event&, const pointer_arrow&) = 0;
	virtual ~active_object() = default;
 };


}//slut på namnrymden
#endif