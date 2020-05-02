#include "include/EventManager.h"

void EventManager::Update()
{
    for (auto && event : events)
    {
        if(event.first.CheckEvent())
        {
            event.second.Activate(&event.first);
        }
    }
}