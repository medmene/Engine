#include "include/EventManager.h"

EventManager* EventManager::em_instance = 0;

EventManager* EventManager::instance()
{
    if(!em_instance)
    {
        em_instance = new EventManager();
        em_instance->events = vector<pair<Event*, Reaction*>>();
    }
    return em_instance;
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