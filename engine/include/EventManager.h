#pragma once
#include "include/Event.h"
#include "include/Reaction.h"
#include "include/Core.h"

class EventManager
{
public:
	static EventManager * instance();
    void RegisterEvent(Event *e, Reaction *r) { events.push_back(pair{e,r}); };
    void Update();
private:
    EventManager() {}
    EventManager( const EventManager& );  
    EventManager& operator=( EventManager& );
    vector<pair<Event*, Reaction*>> events;
	static EventManager			  * sm_instance;
};