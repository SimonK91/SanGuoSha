#ifndef OBJECTS_H
#define OBJECTS_H

#include "../functions.h"
// #include "pointer_arrow.h"
#include <string>
#include <vector>

namespace Object
{

//bashierarkin - abstrakt som bara den
class Object
{
private:

protected:
	//konstruktorer och operatorer som ej används!
	Object() = default;
	Object(const Object&) = delete;
	Object(Object&&) = delete;
	Object& operator=(const Object&) = delete;
	Object& operator=(Object&&) = delete;
	
	SDL_Rect box;
	SDL_Rect clip;
public:
	virtual ~Object(){}
	virtual void paint(SDL_Surface*) = 0;
};

//alla objekt som inte har någon funktion i sig
class DeadObject : public Object
{
private:

protected:

public:
	virtual ~DeadObject() = default;
};

//alla objekt som har en funktion med något kommando.
class ActiveObject : public Object
{
private:

protected:
	int active;
	std::string command;

public:
	ActiveObject() : Object() , active(0), command(""){}
	
	int isActivated(){ return active; }
	virtual std::string handleEvent(const SDL_Event&) = 0;
	virtual ~ActiveObject() = default;
 };


}//slut på namnrymden
#endif