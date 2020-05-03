#include "include/EventManager.h"

EventManager* EventManager::sm_instance = 0;

EventManager::~EventManager()
{
	for (auto && event : events)
	{
		delete event.first;
		delete event.second;
	}
	events.clear();
}

EventManager* EventManager::instance()
{
    if(!sm_instance)
    {
        sm_instance = new EventManager();
        sm_instance->events = vector<pair<Event*, Reaction*>>();
    }
    return sm_instance;
}

void EventManager::Update()
{
    for (auto && event : events)
    {
        if(event.first->CheckEvent())
        {
            event.second->Activate(event.first);
        }
    }
}