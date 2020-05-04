#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Button.h"


class GameObject;
class NPC;

struct Level3
{
	Level3(){}
	~Level3();

	void Init(SDL_Renderer * renderer, const Vector2 & winSize);
	void Update(float dt);
	void Render();

//---------------------------------------------------------------//

	vector<GameObject*>			m_backgrounds;
	vector<GameObject*>			m_grounds;
	vector<GameObject*>			m_objects;
	vector<Button*> 			m_buttons;
	vector<Event*> 				m_events;
	vector<NPC*> 				m_npcs;

	Vector2						m_winSize;
	SDL_Renderer			  * m_renderer;
};