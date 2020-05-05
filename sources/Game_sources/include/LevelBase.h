#pragma once
#include "include/Core.h"
#include "include/Vector2.h"


class GameObject;
class NPC;

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
	vector<NPC*> 				m_npcs;

	Vector2						m_winSize;
	SDL_Renderer			  * m_renderer = nullptr;
	bool						m_deleteLater = false;
};