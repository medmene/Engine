#pragma once
#include "GameObject.h"
#include "Event.h"

class Reaction
{
public:
	Reaction(GameObject *o, void(*func)(GameObject*,Event*)) {object = o;callback = func;}
	void Activate(Event* e) {callback(object,e);}
private:

	GameObject *object;
	void(*callback)(GameObject*,Event*);
};