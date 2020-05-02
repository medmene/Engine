#pragma once
#include "include/Event.h"
#include "include/Reaction.h"
#include "include/Core.h"

class EventManager
{
public:
	EventManager();
	EventManager(const EventManager & other);

    void RegisterEvent(Event e, Reaction r) { events.push_back(pair{e,r}); };
    void Update();
private:
    vector<pair<Event, Reaction>> events;
};