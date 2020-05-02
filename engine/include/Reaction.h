#pragma once
#include "GameObject.h"
#include "Event.h"
#include "Core.h"

class Reaction
{
public:
	Reaction(GameObject *o, function<void(GameObject*,Event*)> func) {object = o;callback = func;}
	void Activate(Event* e) {callback(object,e);}
private:

	GameObject *object;
	function<void(GameObject*,Event*)> callback;
};