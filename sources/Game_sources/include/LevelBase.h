#pragma once
#include "include/Core.h"
#include "include/Vector2.h"


class GameObject;
class NPC;
class Event;

class LevelBase
{
public:
	LevelBase() = default;
	virtual ~LevelBase();

	virtual void Init(SDL_Renderer * renderer, const Vector2 & winSize) = 0;
	void Update(float dt);
	void Render();

	//---------------------------------------------------------------//

	vector<GameObject*>			m_objects;
	// vector<GameObject*>			m_backgrounds;
	// vector<GameObject*>			m_grounds;
	// vector<Button*> 			m_buttons;
	vector<Event*> 				m_events;
	vector<NPC*> 				m_npcs;

	Vector2						m_winSize;
	SDL_Renderer			  * m_renderer = nullptr;
};